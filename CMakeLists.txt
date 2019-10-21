cmake_minimum_required(VERSION 3.13)
project(SFML3D_Test)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(HEADER_FILES include/engine.h include/drawableObject.h)
set(SOURCES src/main.cpp src/engine.cpp)
include_directories(include)

add_executable(SFML3D_Test ${SOURCES} ${HEADER_FILES})
target_link_libraries(SFML3D_Test sfml-graphics sfml-audio sfml-window sfml-system GL)
