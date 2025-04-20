cmake_minimum_required(VERSION 3.15)
project(MyProject)

# Поиск Boost (после Conan)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE Boost::boost Boost::system)