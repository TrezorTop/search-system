cmake_minimum_required(VERSION 3.25)
project(SearchSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        .
)

add_executable(
        SearchSystem
        main.cpp
        modules/DirectoryParser/DirectoryParser.cpp
        modules/DirectoryParser/DirectoryParser.h
        modules/SearchSystem/SearchSystem.cpp
        modules/SearchSystem/SearchSystem.h
)
