cmake_minimum_required(VERSION 3.16)
project(ComputerClub LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    main.cpp
)

add_executable(ComputerClub ${SRC_FILES})

target_include_directories(ComputerClub PRIVATE src)

# Копирование input.txt в выходную директорию
configure_file(${CMAKE_SOURCE_DIR}/input.txt 
               ${CMAKE_BINARY_DIR}/input.txt COPYONLY)