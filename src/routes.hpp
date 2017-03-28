#ifndef SLIM_HTTP_ROUTES_HPP
#define SLIM_HTTP_ROUTES_HPP

#include <map>
#include <memory>
#include <functional>
#include <boost/optional.hpp>

namespace slim_http
{

class route_handler;
class body_route_handler;

class routes
{
public:
    void add_GET_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler);
    void add_POST_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler);
    void add_PUT_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler);
    void add_DELETE_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler);

    boost::optional<std::shared_ptr<route_handler>> get_GET_route_handler(const std::string &path) const;
    boost::optional<std::shared_ptr<body_route_handler>> get_POST_route_handler(const std::string &path) const;
    boost::optional<std::shared_ptr<body_route_handler>> get_PUT_route_handler(const std::string &path) const;
    boost::optional<std::shared_ptr<route_handler>> get_DELETE_route_handler(const std::string &path) const;

private:
    std::map<std::string, std::shared_ptr<route_handler>> _GET_handlers;
    std::map<std::string, std::shared_ptr<body_route_handler>> _POST_handlers;
    std::map<std::string, std::shared_ptr<body_route_handler>> _PUT_handlers;
    std::map<std::string, std::shared_ptr<route_handler>> _DELETE_handlers;
};

}
#endif // SLIM_HTTP_ROUTES_HPP
