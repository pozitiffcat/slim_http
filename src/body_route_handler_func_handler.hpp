#ifndef SLIM_HTTP_BODY_ROUTE_HANDLER_FUNC_HANDLER_HPP
#define SLIM_HTTP_BODY_ROUTE_HANDLER_FUNC_HANDLER_HPP

#include "body_route_handler.hpp"

namespace slim_http
{

template <typename body_t, typename handler>
class body_route_handler_func_handler : public body_route_handler
{
public:
    explicit body_route_handler_func_handler(handler h)
        : _handler(h)
    {
    }

    void prepare_response(const body *b, const request &req, response &res) const
    {
        const body_t *cb = static_cast<const body_t *>(b);
        _handler(cb, req, res);
    }

    std::shared_ptr<body> make_body() const
    {
        return std::make_shared<body_t>();
    }

private:
    handler _handler;
};

}
#endif // SLIM_HTTP_BODY_ROUTE_HANDLER_FUNC_HANDLER_HPP
