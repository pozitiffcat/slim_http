#include "routes.hpp"

namespace slim_http
{

void routes::add(const std::string &method, const std::string &path, routes::handler_func handler)
{
    _handlers[std::make_pair(method, path)] = handler;
}

boost::optional<routes::handler_func> routes::get(const std::string &method, const std::string &path) const
{
    auto it = _handlers.find(std::make_pair(method, path));

    if (it == _handlers.end())
        return boost::none;
    else
        return it->second;
}

}
