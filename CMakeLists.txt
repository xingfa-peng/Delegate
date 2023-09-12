cmake_minimum_required(VERSION 3.4.1)

project(Delegate)

file(GLOB_RECURSE source_files "Sources/*.h" "Sources/*.cpp")

add_executable(Delegate ${source_files} )
