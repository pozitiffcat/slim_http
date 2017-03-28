#ifndef SLIM_HTTP_STRING_RESPONSE_BODY_HPP
#define SLIM_HTTP_STRING_RESPONSE_BODY_HPP

#include <string>
#include "response_body.hpp"

namespace slim_http
{

class string_response_body : public slim_http::response_body
{
public:
    explicit string_response_body(const std::string &str);

    void prepare_response(slim_http::response &res) const;
    const std::vector<char> get_next_part(size_t size);
    size_t get_content_length() const;

private:
    const std::string _str;
    size_t _cursor = 0;
};

}
#endif // SLIM_HTTP_STRING_RESPONSE_BODY_HPP
