cmake_minimum_required(VERSION 3.20)
project(ChatApp LANGUAGES C CXX)

# ----------------- Build‑type -----------------
# Default to Release + -O3 unless caller overrides with
# -DCMAKE_BUILD_TYPE=Debug etc.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# ----------------- Language & flags -----------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect every *.cpp in src/ automatically so you never
# have to touch CMake when you add a new file.
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

# Output binary will be called "runme" so you can simply `./runme`.
add_executable(runme ${SRC_FILES})

target_include_directories(runme PRIVATE ${SRC_DIR})

# Optimisation + “sane” warnings (no -pedantic, no -Werror)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(runme PRIVATE -O3 -Wall -Wextra)
endif()

# ----------------- Raylib -----------------
find_package(raylib 5.0 REQUIRED)

target_link_libraries(runme PRIVATE raylib)

# Linux‑specific extras that raylib needs
if (UNIX AND NOT APPLE)
    target_link_libraries(runme PRIVATE m pthread dl GL)
endif()

# ----------------- Optional DB (comment in later) -----------------
 find_package(SQLite3 REQUIRED)
 target_link_libraries(runme PRIVATE SQLite::SQLite3)

