#ifndef SLIM_HTTP_ROUTES_HPP
#define SLIM_HTTP_ROUTES_HPP

#include <map>
#include <functional>
#include <boost/optional.hpp>

namespace slim_http
{

class request;
class response;

class routes
{
public:
    typedef std::function<void(const request &req, response &res)> handler_func;

public:
    void add(const std::string &method, const std::string &path, handler_func handler);
    boost::optional<handler_func> get(const std::string &method, const std::string &path) const;

private:
    std::map<std::pair<std::string, std::string>, handler_func> _handlers;
};

}
#endif // SLIM_HTTP_ROUTES_HPP
