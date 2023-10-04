cmake_minimum_required(VERSION 3.14)

# 项目名称
project(urd_game)

set(INCLUDE_PATH
    "./include/"
    "../basic/include/"
    "../common/include/"
)

set(SOURCE_FILES
    "./src/main.cpp"
    #"./src/test.cpp"
    "./src/func.cpp"
    "./src/WorldGrid.cpp"
    "./src/Pathfind.cpp"
)

find_package(fmt REQUIRED)
find_package(EnTT REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE urd_common urd_basic)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# option(BUILD_TESTS "Unit test" OFF)
# #if (BUILD_TESTS)
#     add_executable(tests "test/test.cpp")

#     target_include_directories(tests PUBLIC ${INCLUDE_PATH})
#     target_link_libraries(tests PUBLIC ${PROJECT_NAME}) # gtest gtest_main 
# #endif (BUILD_TESTS)