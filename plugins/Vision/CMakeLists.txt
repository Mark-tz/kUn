# VisionModule
set(libs)
# Qt5
find_package(Qt5 COMPONENTS Core REQUIRED)
list(APPEND libs Qt5::Core)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
list(APPEND libs ${PROTOBUF_LIBRARIES})

set(PROTO_LIST
	messages_robocup_ssl_detection
	messages_robocup_ssl_geometry_legacy
	messages_robocup_ssl_geometry
	messages_robocup_ssl_refbox_log
	messages_robocup_ssl_wrapper_legacy
	messages_robocup_ssl_wrapper
	vision_detection
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

include_directories(
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
)

set(HEADERS
	visionmodule.h
	messageformat.h
	${CMAKE_SOURCE_DIR}/Utils/kalmanfilter.h
	${CMAKE_SOURCE_DIR}/Utils/matrix2d.h
)
set(SOURCES
	visionmodule.cpp
	${CMAKE_SOURCE_DIR}/Utils/kalmanfilter.cpp
	${CMAKE_SOURCE_DIR}/Utils/matrix2d.cpp
)
set(SRC
	${HEADERS}
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
)

add_library(zss_vision SHARED ${SRC})

target_link_libraries(zss_vision ${libs})

install(TARGETS zss_vision
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)