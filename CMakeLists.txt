cmake_minimum_required(VERSION 3.10)

# Set the project name
project(dolas_file_creater)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.h")
# ¸´ÖÆÎÄ¼þ
file(COPY template/template.h DESTINATION ${CMAKE_BINARY_DIR})
file(COPY template/template.cpp DESTINATION ${CMAKE_BINARY_DIR})
# Add the executable
add_executable(dolas_file_creater ${SOURCES})