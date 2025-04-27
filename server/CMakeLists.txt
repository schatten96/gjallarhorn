set(tcpserver_target tcp-server)
file(GLOB_RECURSE sources   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_executable(${tcpserver_target} ${sources})
target_link_libraries(${tcpserver_target} PRIVATE   Boost::boost 
                                                 Boost::system)
target_include_directories(${tcpserver_target} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                     ${Boost_INCLUDE_DIRS})