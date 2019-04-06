# VisionModule
set(libs)
# Qt5
find_package(Qt5 COMPONENTS Core REQUIRED)
list(APPEND libs Qt5::Core)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
list(APPEND libs ${PROTOBUF_LIBRARIES})
file(GLOB PROTO_FILES "${CMAKE_SOURCE_DIR}/Utils/Protobuf/*.proto")
protobuf_generate_cpp(PROTO_CPP PROTO_H ${PROTO_FILES})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
)

set(HEADERS
	visionmodule.h
        tinyvisionformat.h
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
