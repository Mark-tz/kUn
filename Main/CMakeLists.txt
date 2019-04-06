# Main

# Qt5
find_package(Qt5 COMPONENTS Core REQUIRED)
list(APPEND libs Qt5::Core)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
list(APPEND libs ${OPENGL_LIBRARIES})

# ODE
find_package(ODE REQUIRED)
include_directories(${ODE_INCLUDE_DIRS})
list(APPEND libs ${ODE_LIBRARIES})
add_definitions(-DdDOUBLE)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
list(APPEND libs ${PROTOBUF_LIBRARIES})

file(GLOB PROTO_FILES "${CMAKE_SOURCE_DIR}/Utils/Protobuf/*.proto")
protobuf_generate_cpp(PROTO_CPP PROTO_H ${PROTO_FILES})


include_directories(
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
	${CMAKE_SOURCE_DIR}/plugins/Sim
	${CMAKE_SOURCE_DIR}/plugins/Vision
)
set(SOURCES
	main.cpp
)
set(SRC
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
)
add_executable(zss_main ${SRC})

target_link_libraries(zss_main zss_simulator zss_vision)

install(TARGETS zss_main RUNTIME DESTINATION bin)