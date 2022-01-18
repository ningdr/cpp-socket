cmake_minimum_required(VERSION 3.20)
project(client)

add_executable(client client.cpp)

target_link_libraries(client PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

target_link_libraries(client PRIVATE ws2_32 PRIVATE wsock32)