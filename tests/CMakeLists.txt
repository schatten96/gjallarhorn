find_package(GTest REQUIRED)

set(gh_tests ghtests)

add_executable(${gh_tests} test.cpp)
target_link_libraries(${gh_tests} PRIVATE GTest::GTest GTest::Main)
set_target_properties(${gh_tests} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)