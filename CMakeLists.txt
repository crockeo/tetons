cmake_minimum_required(VERSION 2.8)
project("tentons")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SOURCES "src/pixel.cpp" "src/image.cpp")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_library(tentons-lib ${SOURCES})

add_executable(tentons src/main.cpp)

target_link_libraries(tentons tentons-lib)
