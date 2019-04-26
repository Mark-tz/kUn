# Simulator Plugin
set(libs)
# OpenGL
find_package(OpenGL REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
list(APPEND libs ${OPENGL_LIBRARIES})

# Qt5
find_package(Qt5 COMPONENTS Core Network Gui REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
)
list(APPEND libs Qt5::Core Qt5::Network Qt5::Gui)

# ODE
find_package(ODE REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS ${ODE_INCLUDE_DIRS})
list(APPEND libs ${ODE_LIBRARIES})
add_definitions(-DdDOUBLE)

# Protobuf
find_package(Protobuf REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIRS})
list(APPEND libs ${PROTOBUF_LIBRARIES})

set(PROTO_LIST
	game_event
	grSim_Commands
	grSimMessage
	grSim_Packet
	grSim_Replacement
	messages_robocup_ssl_detection
	messages_robocup_ssl_geometry_legacy
	messages_robocup_ssl_geometry
	messages_robocup_ssl_refbox_log
	messages_robocup_ssl_wrapper_legacy
	messages_robocup_ssl_wrapper
	referee
	vision_detection
	zss_cmd
	zss_debug
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

list(APPEND PROJECT_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/physics
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
)
include_directories(${PROJECT_INCLUDE_DIRS})

file(GLOB CPPFILES 
	"${CMAKE_SOURCE_DIR}/Utils/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/physics/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/physics/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
set(EXPORT_HEADERS
	sslworld.h
)
set(HEADERS
	${EXPORT_HEADERS}
)
set(SOURCES
	sslworld.cpp
)
set(srcs
    ${PROTO_CPP}
    ${PROTO_H}
    ${HEADERS}
    ${SOURCES}
    ${CPPFILES}
)

set(target_lib zss_simulator)

if(BUILD_PYTHON_PLUGINS)
	execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
	list(INSERT CMAKE_MODULE_PATH 0 ${CPYY_MODULE_PATH})
	find_package(Cppyy)
endif()

add_library(${target_lib} SHARED ${srcs})

set_target_properties(${target_lib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${target_lib} PUBLIC ${PROJECT_INCLUDE_DIRS})

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
