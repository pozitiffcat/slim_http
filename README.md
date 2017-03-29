# Simple Http Server Library
### Features:
* routes
* headers
* body
* c++14
* boost

### Installation
Add sources from git into yor path:
```bash
git submodule add https://github.com/pozitiffcat/slim_http.git slim_http
```
or:
```bash
git checkout https://github.com/pozitiffcat/slim_http.git slim_http
```

Add into CMakeLists.txt:
```cmake
add_definitions(-DBOOST_LOG_DYN_LINK)
add_subdirectory(slim_http)
include_directories(slim_http/src)
target_link_libraries(${PROJECT_NAME} slim_http)
```

### Example:
```c++
#include <memory>
#include <boost/log/utility/setup/console.hpp>

#include "server.hpp"
#include "response.hpp"
#include "async_token.hpp"
#include "string_body.hpp"
#include "string_response_body.hpp"
#include "file_response_body.hpp"

int main(int argc, char *argv[])
{
    boost::log::add_console_log(std::clog, boost::log::keywords::format = ">> %Message%");

    boost::asio::io_service service;

    slim_http::server server(service, 8080);

    server.add_GET_route_handler_func("/", [&service](const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::string_response_body>("result text"));
    });

    server.add_GET_route_handler_func("/async", [&service](const auto &req, auto &res){
        auto async_token = res.set_async();
        auto timer = std::make_shared<boost::asio::deadline_timer>(service, boost::posix_time::seconds(5));
        timer->async_wait([async_token, timer, &res](auto e){
            res.set_response_body(std::make_shared<slim_http::string_response_body>("result text"));
            async_token->handle();
        });
    });

    server.add_POST_route_handler_func<slim_http::string_body>("/echo", [](auto b, const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::string_response_body>("echo: " + b->get_string()));
    });

    server.add_GET_route_handler_func("/download", [](const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::file_response_body>("/home/alexey/ubuntu-16.10-server-amd64.iso"));
    });

    service.run();

    return 0;
}

```
