#ifndef SLIM_HTTP_RESPONSE_HPP
#define SLIM_HTTP_RESPONSE_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "headers.hpp"

namespace slim_http
{

class async_token;
class response_body;

class response : public std::enable_shared_from_this<response>
{
public:
    typedef std::function<void(const boost::system::error_code &)> handler_func;

public:
    explicit response(boost::asio::ip::tcp::socket &socket);

    void set_response_code(int response_code);
    void set_content_type(const std::string &content_type);
    void set_response_body(const std::shared_ptr<response_body> &b);
    void set_header(const std::string &name, const std::string &value);
    std::shared_ptr<async_token> set_async();

    void start(handler_func handler);

private:
    void write_response(handler_func handler);
    void write_next_part_body(response::handler_func handler);

private:
    boost::asio::ip::tcp::socket &_socket;
    int _response_code = 200;
    std::shared_ptr<response_body> _body;
    std::vector<char> _buffer;
    size_t _buffer_availdable;
    headers _headers;
    std::shared_ptr<async_token> _async_token;
};

}
#endif // SLIM_HTTP_RESPONSE_HPP
