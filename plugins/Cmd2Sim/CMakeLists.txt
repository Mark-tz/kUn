# Cmd2Sim
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

file(GLOB CPPFILES 
	"${CMAKE_SOURCE_DIR}/Utils/*.cpp"
)

set(HEADERS
	cmd2sim.cpp
)
set(SOURCES
	cmd2sim.h
)
set(SRC
	${HEADERS}
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
	${CPPFILES}
)

add_library(zss_cmd2sim SHARED ${SRC})

target_link_libraries(zss_cmd2sim ${libs})

install(TARGETS zss_cmd2sim
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)