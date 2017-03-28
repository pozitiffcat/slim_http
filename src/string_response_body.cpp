#include "response.hpp"
#include "string_response_body.hpp"

namespace slim_http
{

slim_http::string_response_body::string_response_body(const std::string &str)
    : _str(str)
{
}

void string_response_body::prepare_response(slim_http::response &res) const
{
    res.set_content_type("text/plain");
}

const std::vector<char> string_response_body::get_next_part(size_t size)
{
    if (_cursor + size > _str.size())
        size = _str.size() - _cursor;

    if (size)
    {
        std::vector<char> result(_str.data() + _cursor, _str.data() + _cursor + size);
        _cursor += size;
        return std::move(result);
    }
    else
    {
        return std::vector<char>();
    }
}

size_t string_response_body::get_content_length() const
{
    return _str.size();
}

}
