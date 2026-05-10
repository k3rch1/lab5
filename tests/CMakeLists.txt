add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../googletest
    googletest-build
)

enable_testing()

add_executable(
    tests
    dynamic_array_tests.cpp
    linked_list_tests.cpp
    array_sequence_tests.cpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(
    tests
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)