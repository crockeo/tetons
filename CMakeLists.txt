cmake_minimum_required(VERSION 2.8)
project("tetons")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SOURCES "src/pixel.cpp"
            "src/image.cpp"
            "src/load.cpp")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_library(tetons-lib ${SOURCES})

add_executable(tetons src/main.cpp)

target_link_libraries(tetons tetons-lib)
