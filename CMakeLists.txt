cmake_minimum_required(VERSION 3.16)

project(SampleProject)

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

add_test(
    NAME StudyRecordTest
    COMMAND study_app_test
)