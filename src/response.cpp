#include "response.hpp"
#include "response_body.hpp"

namespace slim_http
{

response::response(boost::asio::ip::tcp::socket &socket)
    : _socket(socket)
{
}

void response::set_response_code(int response_code)
{
    _response_code = response_code;
}

void response::set_content_type(const std::string &content_type)
{
    _headers.append("Content-Type", content_type);
}

void response::set_response_body(const std::shared_ptr<response_body> &b)
{
    _body = b;
}

void response::set_header(const std::string &name, const std::string &value)
{
    _headers.replace(name, value);
}

void response::start(response::handler_func handler)
{
    std::stringstream str_str;
    str_str << "HTTP/1.1 " << _response_code << "\r\n";

    if (_body)
    {
        str_str << "Content-Length: " << _body->get_content_length() << "\r\n";
        _buffer_availdable = _body->get_content_length();
        _body->prepare_response(*this);
    }

    for (const auto &p :_headers.get_pair_list())
        str_str << p.first << ": " << p.second << "\r\n";

    str_str << "\r\n";

    auto self = shared_from_this();
    _socket.async_write_some(boost::asio::buffer(str_str.str()), [this, handler, self](auto e, auto t){
        if (!e)
        {
            if (_body)
                this->write_next_part_body(handler);
            else
                handler(boost::system::error_code());
        }
        else
        {
            handler(e);
        }
    });
}

void response::write_next_part_body(response::handler_func handler)
{
    size_t size = _buffer_availdable > 1024 * 512 ? 1024 * 512 : _buffer_availdable;
    _buffer = _body->get_next_part(size);
    _buffer_availdable -= _buffer.size();

    auto self = shared_from_this();
    boost::asio::async_write(_socket, boost::asio::buffer(_buffer), [this, size, handler, self](auto e, auto t){
        if (!e)
        {
            if (t != _buffer.size())
                BOOST_LOG_TRIVIAL(warning) << "sended response part is not equal its size";

            if (_buffer_availdable)
            {
                this->write_next_part_body(handler);
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

}
