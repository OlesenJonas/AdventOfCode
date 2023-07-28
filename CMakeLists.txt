cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# #############################################################################
project(AdventOfCode)

# #############################################################################

# Compiler Commands etc
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# clangd requires a compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DNOMINMAX) # dont want windows.h or other predefined min/max functions

# #############################################################################
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)

# on windows RUNTIME_OUTPUT decides where .dll s will be put
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/out/debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)

# on windows RUNTIME_OUTPUT decides where .dll s will be put
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/out/release)

# #############################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/")