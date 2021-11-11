cmake_minimum_required(VERSION 3.20)
project(correct)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)

add_executable(correct correct.cpp)

target_include_directories(correct PUBLIC
        ${SPDLOG_INCLUDE_DIR}
        )