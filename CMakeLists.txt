set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "")

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(ppf_object_recognition)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ppf_object_recognition ppf_object_recognition.cpp)
target_link_libraries (ppf_object_recognition ${PCL_LIBRARIES})
