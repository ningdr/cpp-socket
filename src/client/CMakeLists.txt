cmake_minimum_required(VERSION 3.20)
project(client)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(client client.cpp)

target_include_directories(client PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )

target_link_libraries(client PUBLIC
        ws2_32
        wsock32
)