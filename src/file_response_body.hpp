#ifndef SLIM_HTTP_FILE_RESPONSE_BODY_HPP
#define SLIM_HTTP_FILE_RESPONSE_BODY_HPP

#include <boost/filesystem.hpp>
#include "response_body.hpp"

namespace slim_http
{

class file_response_body : public slim_http::response_body
{
public:
    explicit file_response_body(const std::string &filename);

    void prepare_response(slim_http::response &res) const;
    const std::vector<char> get_next_part(size_t size);
    size_t get_content_length() const;

private:
    std::ifstream _stream;
    boost::filesystem::path _path;
    size_t _size;
};

}
#endif // SLIM_HTTP_FILE_RESPONSE_BODY_HPP
