#ifndef SLIM_HTTP_SERVER_HPP
#define SLIM_HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "routes.hpp"
#include "route_handler_func_handler.hpp"
#include "body_route_handler_func_handler.hpp"

namespace slim_http
{

class request;
class response;
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

    template <typename handler_func>
    void add_GET_route_handler_func(const std::string &path, handler_func handler)
    {
        add_GET_route_handler(path, std::make_shared<route_handler_func_handler<handler_func>>(handler));
    }

    template <typename body_t, typename handler_func>
    void add_POST_route_handler_func(const std::string &path, handler_func handler)
    {
        add_POST_route_handler(path, std::make_shared<body_route_handler_func_handler<body_t, handler_func>>(handler));
    }

    template <typename body_t, typename handler_func>
    void add_PUT_route_handler_func(const std::string &path, handler_func handler)
    {
        add_PUT_route_handler(path, std::make_shared<body_route_handler_func_handler<body_t, handler_func>>(handler));
    }

    template <typename handler_func>
    void add_DELETE_route_handler_func(const std::string &path, handler_func handler)
    {
        add_DELETE_route_handler(path, std::make_shared<route_handler_func_handler<handler_func>>(handler));
    }

private:
    void new_accept();

private:
    boost::asio::ip::tcp::acceptor _acceptor;
    routes _routes;
};

}
#endif // SLIM_HTTP_SERVER_HPP
