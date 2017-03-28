#ifndef SLIM_HTTP_SERVER_HPP
#define SLIM_HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

namespace slim_http
{

class server
{
public:
    server(boost::asio::io_service &service, int port);

private:
    void new_accept();

private:
    boost::asio::ip::tcp::acceptor _acceptor;
};

}
#endif // SLIM_HTTP_SERVER_HPP
