cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.60.0 REQUIRED COMPONENTS date_time filesystem system log)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCES_LIST src/*.cpp)

add_library(slim_http STATIC ${SOURCES_LIST})
target_link_libraries(slim_http ${Boost_LIBRARIES} pthread)
