cmake_minimum_required(VERSION 3.14)

project(urd_common)

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(SOURCE_FILES
    "./src/color.cpp"
    "./src/mathf.cpp"
    "./src/rect.cpp"
    "./src/vec2.cpp"
    "./src/vec2i.cpp"
    "./include/common/StepViewer.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests/")