#include "response.hpp"
#include "file_response_body.hpp"

namespace slim_http
{

slim_http::file_response_body::file_response_body(const std::string &filename)
    : _stream(filename, std::ios::in),
      _path(boost::filesystem::path(filename)),
      _size(boost::filesystem::file_size(filename))
{
}

void file_response_body::prepare_response(response &res) const
{
    std::string name = _path.filename().string();
    res.set_content_type("application/octet-stream");
    res.set_header("Content-Disposition", "attachment; filename=\"" + name + "\"");
    res.set_header("Content-Transfer-Encoding", "binary");
    res.set_header("Accept-Ranges", "bytes");
}

const std::vector<char> file_response_body::get_next_part(size_t size)
{
    std::vector<char> result(size);
    size = _stream.readsome(result.data(), size);
    result.resize(size);
    return std::move(result);
}

size_t file_response_body::get_content_length() const
{
    return _size;
}

}
