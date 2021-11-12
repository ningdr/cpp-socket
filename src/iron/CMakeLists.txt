cmake_minimum_required(VERSION 3.20)
project(iron)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(iron iron.cpp)

target_include_directories(iron PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )