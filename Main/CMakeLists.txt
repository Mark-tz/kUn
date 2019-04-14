# Main

# Qt5
find_package(Qt5 COMPONENTS Core REQUIRED)
# list(APPEND libs Qt5::Core)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
# list(APPEND libs ${OPENGL_LIBRARIES})

# ODE
find_package(ODE REQUIRED)
include_directories(${ODE_INCLUDE_DIRS})
# list(APPEND libs ${ODE_LIBRARIES})
# add_definitions(-DdDOUBLE)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
# list(APPEND libs ${PROTOBUF_LIBRARIES})

set(PROTO_LIST
	messages_robocup_ssl_detection
	messages_robocup_ssl_geometry_legacy
	messages_robocup_ssl_geometry
	messages_robocup_ssl_refbox_log
	messages_robocup_ssl_wrapper_legacy
	messages_robocup_ssl_wrapper
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})


include_directories(
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
	${CMAKE_SOURCE_DIR}/plugins
)
set(SOURCES
	main.cpp
)
set(SRC
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
)

set(zss_lib
	zss_simulator
    zss_vision
    zss_decision
)


add_executable(zss_main ${SRC})

target_link_libraries(zss_main ${zss_lib})

install(TARGETS zss_main RUNTIME DESTINATION bin)
