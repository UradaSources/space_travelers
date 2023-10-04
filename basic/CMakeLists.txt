cmake_minimum_required(VERSION 3.14)

project(urd_basic)

set(INCLUDE_PATH 
    "./include/"
    "../common/include/")

set(SOURCE_FILES
    "./src/input.cpp"
    "./src/visual.cpp")

find_package(raylib REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE urd_common raylib)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)