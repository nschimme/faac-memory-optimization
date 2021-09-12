cmake_minimum_required(VERSION 3.10)

project (faac_static LANGUAGES C)
add_compile_options(-Wall -O2 -g)
set(CMAKE_BUILD_TYPE "Debug")

include_directories(./include)

add_subdirectory(${PROJECT_SOURCE_DIR}/libfaac)

# ≤‚ ‘≥Ã–Ú
add_executable(test.exe test.c)
target_link_libraries(test.exe faac m)
