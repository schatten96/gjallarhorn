set(tcpclient_target tcp-client)
file(GLOB_RECURSE tcp_sources   ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp/*.cpp
                                ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp/*.hpp
                                )
add_executable(${tcpclient_target} ${tcp_sources})
target_link_libraries(${tcpclient_target} PRIVATE   Boost::boost 
                                                    Boost::system
                                                    )
target_include_directories(${tcpclient_target} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                        ${Boost_INCLUDE_DIRS}
                                                        )