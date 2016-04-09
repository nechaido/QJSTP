cmake_minimum_required(VERSION 3.4)
project(QJSTP)

set(CMAKE_PREFIX_PATH lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp QJSTP.cpp QJSTP.h)

find_package(Qt5 REQUIRED COMPONENTS Core Script)

add_executable(QJSTP ${SOURCE_FILES})

target_link_libraries(QJSTP Qt5::Core Qt5::Script)
