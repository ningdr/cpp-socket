cmake_minimum_required(VERSION 3.20)
project(server)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(server server.cpp)

target_include_directories(server PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )

target_link_libraries(server PUBLIC
        ws2_32
        wsock32
)