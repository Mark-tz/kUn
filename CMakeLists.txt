cmake_minimum_required(VERSION 3.9)
project(Kun LANGUAGES CXX)

if(BUILD_PYTHON)
	message("BUILD_PYTHON : true")
	set(BUILD_PYTHON_PLUGINS true)
else()
	message("BUILD_PYTHON : false")
	set(BUILD_PYTHON_PLUGINS false)
endif()

find_package(Protobuf REQUIRED)
function(get_pb_file H CPP)
	list(APPEND PH ${ARGN})
	list(APPEND PC ${ARGN})
	list(TRANSFORM PH PREPEND ${CMAKE_BINARY_DIR}/proto/)
	list(TRANSFORM PH APPEND .pb.h)
	list(TRANSFORM PC PREPEND ${CMAKE_BINARY_DIR}/proto/)
	list(TRANSFORM PC APPEND .pb.cc)
	set(${H} ${PH} PARENT_SCOPE)
	set(${CPP} ${PC} PARENT_SCOPE)
endfunction()
SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
file(MAKE_DIRECTORY ${PROTO_META_BASE_DIR})
LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR}/Utils/Protobuf)
file(GLOB PROTO_FILES "${CMAKE_SOURCE_DIR}/Utils/Protobuf/*.proto")
# protobuf_generate_cpp(PROTO_CPP PROTO_H ${PROTO_FILES})
FOREACH(FIL ${PROTO_FILES})
	GET_FILENAME_COMPONENT(ABS_FIL ${FIL} ABSOLUTE)
	GET_FILENAME_COMPONENT(FIL_WE ${ABS_FIL} NAME_WE)
	EXECUTE_PROCESS(
		COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
ENDFOREACH()

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


set(VERSION "0.0.1")
set(VENDOR "ZJUNlict")
set(MAINTAINER "ZJUNlict <zjunlict.ssl@gmail.com>")
set(OpenGL_GL_PREFERENCE "LEGACY")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
include(${PROJECT_SOURCE_DIR}/cmake/Utils.cmake)
standard_config()
standard_paths(${PROJECT_SOURCE_DIR} bin lib)

set(CMAKE_CXX_STANDARD 17)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

add_subdirectory(plugins)
add_subdirectory(Main)


find_package(Qt5 COMPONENTS Core REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}
)
set(EXPORT_HEADERS
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin/zsplugin.hpp
)
set(srcs
	${EXPORT_HEADERS}
)
set(target_lib zss_plugin)

if(BUILD_PYTHON_PLUGINS)
	execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
	list(INSERT CMAKE_MODULE_PATH 0 ${CPYY_MODULE_PATH})
	find_package(Cppyy)
endif()
add_library(${target_lib} SHARED ${srcs})

set_target_properties(${target_lib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
# target_include_directories(${target_lib} PUBLIC ${PROJECT_INCLUDE_DIRS})
if(BUILD_PYTHON_PLUGINS)
	cppyy_add_bindings(
	   "${target_lib}" "0.0.1" "ZJUNlict" "zjunlict.ssl@gmail.com"
	   LANGUAGE_STANDARD "17"
	   GENERATE_OPTIONS "-D__PIC__;-Wno-macro-redefined"
	   INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS}
	   LINK_LIBRARIES ${target_lib}
	   H_DIRS ${PROJECT_INCLUDE_DIRS}
	   H_FILES ${EXPORT_HEADERS})
endif()
target_link_libraries(${target_lib} ${libs})

install(TARGETS ${target_lib}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
