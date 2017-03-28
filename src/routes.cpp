#include "routes.hpp"

namespace slim_http
{

void routes::add_GET_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler)
{
    _GET_handlers[path] = handler;
}

void routes::add_POST_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler)
{
    _POST_handlers[path] = handler;
}

void routes::add_PUT_route_handler(const std::string &path, const std::shared_ptr<body_route_handler> &handler)
{
    _PUT_handlers[path] = handler;
}

void routes::add_DELETE_route_handler(const std::string &path, const std::shared_ptr<route_handler> &handler)
{
    _DELETE_handlers[path] = handler;
}

boost::optional<std::shared_ptr<route_handler> > routes::get_GET_route_handler(const std::string &path) const
{
    auto it = _GET_handlers.find(path);

    if (it != _GET_handlers.end())
        return it->second;
    else
        return boost::none;
}

boost::optional<std::shared_ptr<body_route_handler> > routes::get_POST_route_handler(const std::string &path) const
{
    auto it = _POST_handlers.find(path);

    if (it != _POST_handlers.end())
        return it->second;
    else
        return boost::none;
}

boost::optional<std::shared_ptr<body_route_handler> > routes::get_PUT_route_handler(const std::string &path) const
{
    auto it = _PUT_handlers.find(path);

    if (it != _PUT_handlers.end())
        return it->second;
    else
        return boost::none;
}

boost::optional<std::shared_ptr<route_handler> > routes::get_DELETE_route_handler(const std::string &path) const
{
    auto it = _DELETE_handlers.find(path);

    if (it != _DELETE_handlers.end())
        return it->second;
    else
        return boost::none;
}

}
