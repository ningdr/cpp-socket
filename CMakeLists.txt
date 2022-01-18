cmake_minimum_required(VERSION 3.20)
project(socket)

set(CMAKE_CXX_STANDARD 11)
# -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
# 设定可执行二进制文件的目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设定存放编译出来的库文件的目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(spdlog CONFIG REQUIRED)

add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(src/apple)
add_subdirectory(src/correct)
add_subdirectory(src/iron)
add_subdirectory(src/coin_change)

# 并且把该目录设为连接目录
link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

include_directories(
        ${SPDLOG_INCLUDE_DIR}
)