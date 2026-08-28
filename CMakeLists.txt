cmake_minimum_required(VERSION 3.16)

project(SampleProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(study_app
    src/main.cpp
    src/StudyRecord.cpp
    src/StudyManager.cpp
)

target_include_directories(study_app PRIVATE include)