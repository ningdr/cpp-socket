cmake_minimum_required(VERSION 3.20)
project(apple)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(apple apple.cpp)

target_include_directories(apple PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )

target_link_libraries(apple PUBLIC
        ws2_32
        wsock32
)