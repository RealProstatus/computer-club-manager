cmake_minimum_required(VERSION 3.16)

project(ComputerClub LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(ComputerClub
    ${SRC_FILES}
    ${CMAKE_SOURCE_DIR}/main.cpp
)

# Выводим список подключённых исходников (для отладки конфигурации)
message(STATUS "Source files: ${SRC_FILES}")

# Устанавливаем выводимый файл в корневую папку билда (по умолчанию build/)
set_target_properties(ComputerClub PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)