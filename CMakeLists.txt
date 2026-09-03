cmake_minimum_required(VERSION 3.16)

project(SampleProject)
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(study_app
    src/main.cpp
    src/StudyRecord.cpp
    src/StudyManager.cpp
    src/MainManager.cpp
)

target_include_directories(study_app PRIVATE include)

add_executable(study_app_test
    tests/StudyRecordTest.cpp
    src/StudyRecord.cpp
)

target_include_directories(study_app_test PRIVATE include)

enable_testing()
target_link_libraries(
    study_app_test
    PRIVATE
    GTest::gtest_main
)

add_executable(study_manager_test
    tests/StudyManagerTest.cpp
    src/StudyManager.cpp
    src/StudyRecord.cpp
)

target_include_directories(study_manager_test PRIVATE include)

target_link_libraries(
    study_manager_test
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(study_app_test)
gtest_discover_tests(study_manager_test)
