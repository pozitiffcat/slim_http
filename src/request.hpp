#ifndef SLIM_HTTP_REQUEST_HPP
#define SLIM_HTTP_REQUEST_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "headers.hpp"

namespace slim_http
{

class request : public std::enable_shared_from_this<request>
{
public:
    typedef std::function<void(const boost::system::error_code &)> handler_func;

public:
    explicit request(boost::asio::ip::tcp::socket &socket);

    const std::string &method() const;
    const std::string &path() const;
    const std::string &version() const;

    void start(handler_func handler);

private:
    enum state
    {
        state_method,
        state_path,
        state_version,
        state_firstline_n,
        state_header_name,
        state_header_value,
        state_header_n,
        state_last_header_n,
        state_body,
        state_end
    };

private:
    void parse_part(size_t size);

private:
    boost::asio::ip::tcp::socket &_socket;
    std::array<char, 1024> _buffer;
    headers _headers;
    std::string _method;
    std::string _path;
    std::string _version;
    std::string _header_name;
    std::string _header_value;
    state _state = state_method;
};

}
#endif // SLIM_HTTP_REQUEST_HPP
