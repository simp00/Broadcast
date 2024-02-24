cmake_minimum_required(VERSION 3.18)
project(BroadCast)

include_directories(../3rd/asio-1.28.0/include)
set(CMAKE_CXX_STANDARD 17)

add_executable(BroadCast main.cpp)
target_link_libraries(BroadCast pthread)
