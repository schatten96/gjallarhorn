cmake_minimum_required(VERSION 3.15)
project(MyProject)

if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
else()
    message(FATAL_ERROR "conan_toolchain.cmake not found! Run 'conan install' first.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS system)

add_subdirectory(common)
# add_subdirectory(ui)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(tests)
