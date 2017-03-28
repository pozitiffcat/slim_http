#ifndef SLIM_HTTP_RESPONSE_HPP
#define SLIM_HTTP_RESPONSE_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

namespace slim_http
{

class response : public std::enable_shared_from_this<response>
{
public:
    typedef std::function<void(const boost::system::error_code &)> handler_func;

public:
    explicit response(boost::asio::ip::tcp::socket &socket);

    void start(handler_func handler);

private:
    boost::asio::ip::tcp::socket &_socket;
};

}
#endif // SLIM_HTTP_RESPONSE_HPP
