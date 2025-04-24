set(server_target server)
file(GLOB_RECURSE sources   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_executable(${server_target} ${sources})
target_link_libraries(${server_target} PRIVATE   Boost::boost 
                                                 Boost::system)
target_include_directories(${server_target} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                     ${Boost_INCLUDE_DIRS})