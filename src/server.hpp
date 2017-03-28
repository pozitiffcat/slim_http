#ifndef SLIM_HTTP_SERVER_HPP
#define SLIM_HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "routes.hpp"

namespace slim_http
{

class route_handler;
class body_route_handler;

class server
{
public:
    server(boost::asio::io_service &service, int port);

    void add_GET_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler);
    void add_POST_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler);
    void add_PUT_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler);
    void add_DELETE_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler);

private:
    void new_accept();

private:
    boost::asio::ip::tcp::acceptor _acceptor;
    routes _routes;
};

}
#endif // SLIM_HTTP_SERVER_HPP
