cmake_minimum_required(VERSION 3.14)
project(algorithms_data_structures VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(dynamic_matrix_test tests/dynamic_matrix_test.cpp source/dynamic_matrix.h)
target_link_libraries(dynamic_matrix_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_executable(red_black_tree_test tests/red_black_tree_test.cpp source/red_black_tree.h)
# target_link_libraries(red_black_tree_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
# include(GoogleTest)
# gtest_discover_tests(red_black_tree_test)