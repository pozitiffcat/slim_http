#ifndef SLIM_HTTP_ROUTE_HANDLER_FUNC_HANDLER_HPP
#define SLIM_HTTP_ROUTE_HANDLER_FUNC_HANDLER_HPP

#include "route_handler.hpp"

namespace slim_http
{

template <typename handler>
class route_handler_func_handler : public route_handler
{
public:
    explicit route_handler_func_handler(handler h)
        : _handler(h)
    {
    }

    void prepare_response(const request &req, response &res) const
    {
        _handler(req, res);
    }

private:
    handler _handler;
};

}
#endif // SLIM_HTTP_ROUTE_HANDLER_FUNC_HANDLER_HPP
