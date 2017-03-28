#include "string_body.hpp"

namespace slim_http
{

void slim_http::string_body::put_bytes(const char *data, size_t size)
{
    while (size--)
    {
        _str += *data++;
    }
}

const std::string &string_body::get_string() const
{
    return _str;
}

}
