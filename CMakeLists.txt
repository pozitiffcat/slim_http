cmake_minimum_required(VERSION 2.8)

#library

set(CMAKE_CXX_STANDARD 14)
file(GLOB SOURCES_LIST src/*.cpp)
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.63.0 REQUIRED COMPONENTS date_time filesystem system log)
include_directories(${Boost_INCLUDE_DIRS})
add_library(slim_http ${SOURCES_LIST})
link_libraries(slim_http ${Boost_LIBRARIES} pthread)

# test

include_directories(src)
add_executable(test  "main.cpp")
link_libraries(test slim_http)
