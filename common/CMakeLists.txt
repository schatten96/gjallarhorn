set(ghcommon_target ghcommon)
file(GLOB_RECURSE gh_common_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
                                    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                                    )
add_library(${ghcommon_target} SHARED ${gh_common_sources})
target_include_directories(${ghcommon_target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)