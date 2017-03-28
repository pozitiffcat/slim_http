#include "body.hpp"
#include "request.hpp"

namespace slim_http
{

request::request(boost::asio::ip::tcp::socket &socket)
    : _socket(socket)
{
}

const std::string &request::method() const
{
    return _method;
}

const std::string &request::path() const
{
    return _path;
}

const std::string &request::version() const
{
    return _version;
}

void request::start(request::handler_func handler)
{
    auto self = shared_from_this();
    _socket.async_read_some(boost::asio::buffer(_buffer), [this, handler, self](auto e, auto t){
        if (!e)
        {
            if (t != 0)
            {
                this->parse_part(t);

                if (_state != state_end && _state != state_body)
                    this->start(handler);
                else
                    handler(boost::system::error_code());
            }
            else
            {
                handler(boost::system::error_code());
            }
        }
        else
        {
            handler(e);
        }
    });
}

void request::write_body(const std::shared_ptr<body> &body, handler_func handler)
{
    if (_state == state_body)
    {
        if (_buffer_position < _buffer_size)
        {
            body->put_bytes(_buffer.data() + _buffer_position, _buffer_size - _buffer_position);
            size_t sz = (_buffer_size - _buffer_position);
            _buffer_available -= (sz > _buffer_available ? _buffer_available : sz);
        }

        if (_buffer_available)
        {
            size_t for_read =_buffer_available > _buffer.size() ? _buffer.size() : _buffer_available;
            auto self = shared_from_this();
            _socket.async_read_some(boost::asio::buffer(_buffer), [this, body, handler, self](auto e, auto t){
                if (!e)
                {
                    _buffer_position = 0;
                    _buffer_size = t;
                    this->write_body(body, handler);
                }
                else
                {
                    handler(e);
                }
            });
        }
        else
        {
            _state = state_end;
            handler(boost::system::error_code());
        }
    }
}

void request::parse_part(size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        char c = _buffer[i];

        switch (_state)
        {
        case state_method:
            if (c != ' ')
                _method += c;
            else
                _state = state_path;
            break;
        case state_path:
            if (c != ' ')
                _path += c;
            else
                _state = state_version;
            break;
        case state_version:
            if (c != '\r')
                _version += c;
            else
                _state = state_firstline_n;
            break;
        case state_firstline_n:
            if (c == '\n')
                _state = state_header_name;
            break;
        case state_header_name:
            if (_header_name.empty() && c == '\r')
                _state = state_last_header_n;
            else if (c != ':')
                _header_name += c;
            else
                _state = state_header_value;
            break;
        case state_header_value:
            if (c != '\r')
                _header_value += c;
            else
                _state = state_header_n;
            break;
        case state_header_n:
            if (c == '\n')
            {
                _state = state_header_name;
                _headers.append(_header_name, _header_value);

                BOOST_LOG_TRIVIAL(debug) << _header_name << ":" << _header_value;

                _header_name.clear();
                _header_value.clear();
            }
            break;
        case state_last_header_n:
            if (c == '\n')
            {
                auto content_length_opt = _headers.get("Content-Length");
                if (content_length_opt)
                {
                    int content_length = std::stoi(content_length_opt.get());
                    _state = state_body;
                    _buffer_position = i + 1;
                    _buffer_size = size;
                    _buffer_available = content_length;
                    return;
                }
                else
                {
                    _state = state_end;
                }
            }
            break;
        }
    }
}

}
