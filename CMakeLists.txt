cmake_minimum_required (VERSION 3.20)
project ("use_folly_examle")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /Oi /Zi /Ot /GL /MD")

file(GLOB_RECURSE CONFIG_DIRS "${PROJECT_SOURCE_DIR}/deps/*/*config.cmake")
foreach(CONFIG_FILE ${CONFIG_DIRS})
    get_filename_component(PARENT_DIR ${CONFIG_FILE} DIRECTORY)
    list(APPEND CMAKE_PREFIX_PATH ${PARENT_DIR})
endforeach()

message(${CMAKE_PREFIX_PATH})
include(CMakeFindDependencyMacro)
find_dependency(gflags REQUIRED)
find_dependency(glog REQUIRED)
find_dependency(Folly REQUIRED)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES ${SRC_DIR}/*.h ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Folly::folly)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:gflags_shared> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:glog::glog> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
