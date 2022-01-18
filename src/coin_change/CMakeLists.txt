cmake_minimum_required(VERSION 3.20)
project(coin_change)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(coin_change coin_change.cpp)

target_include_directories(coin_change PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )