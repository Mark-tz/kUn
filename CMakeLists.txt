cmake_minimum_required(VERSION 3.9)
project(Kun)

set(VERSION "0.0.1")
set(VENDOR "ZJUNlict")
set(MAINTAINER "ZJUNlict <zjunlict.ssl@gmail.com>")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
include(${PROJECT_SOURCE_DIR}/cmake/Utils.cmake)
standard_config()
standard_paths(${PROJECT_SOURCE_DIR} bin lib)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(plugins)
add_subdirectory(Main)