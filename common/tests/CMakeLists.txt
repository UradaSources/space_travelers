cmake_minimum_required(VERSION 3.14)

project(urd_common_test)

find_package(Catch2 CONFIG REQUIRED)

set(SOURCE_FILES
	"./test.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")
target_link_libraries(${PROJECT_NAME} PRIVATE urd_common Catch2::Catch2WithMain)

enable_testing()
add_test(NAME urd_common COMMAND ${PROJECT_NAME})