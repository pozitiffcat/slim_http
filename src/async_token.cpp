#include <stdexcept>
#include "async_token.hpp"

namespace slim_http
{

void async_token::handle()
{
    if (_handler)
    {
        auto func = _handler;
        _handler = nullptr;
        func();
    }
    else
    {
        throw std::runtime_error("the token is handled already");
    }
}

void async_token::set_handler(async_token::handler_func handler)
{
    _handler = handler;
}

}
