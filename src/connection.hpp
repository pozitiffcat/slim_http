#ifndef SLIM_HTTP_CONNECTION_HPP
#define SLIM_HTTP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

namespace slim_http
{

class routes;

class connection : public std::enable_shared_from_this<connection>
{
public:
    connection(boost::asio::io_service &service, const routes &r);
    ~connection();

    boost::asio::ip::tcp::socket &get_socket();

    void start();

private:
    boost::asio::ip::tcp::socket _socket;
    const routes &_routes;
};

}
#endif // SLIM_HTTP_CONNECTION_HPP
