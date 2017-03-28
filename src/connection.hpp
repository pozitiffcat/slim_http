#ifndef SLIM_HTTP_CONNECTION_HPP
#define SLIM_HTTP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

namespace slim_http
{

class connection : public std::enable_shared_from_this<connection>
{
public:
    explicit connection(boost::asio::io_service &service);
    ~connection();

    boost::asio::ip::tcp::socket &get_socket();

    void start();

private:
    boost::asio::ip::tcp::socket _socket;
};

}
#endif // SLIM_HTTP_CONNECTION_HPP
