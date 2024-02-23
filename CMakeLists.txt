cmake_minimum_required(VERSION 3.24)
project(BroadCast)

include_directories(Asio/asio/include)
set(CMAKE_CXX_STANDARD 17)

add_executable(BroadCast main.cpp)
