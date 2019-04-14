# DecisionModule
set(libs)
# Qt5
find_package(Qt5 COMPONENTS Core Network REQUIRED)
list(APPEND libs Qt5::Core Qt5::Network)

# Protobuf
# find_package(Protobuf REQUIRED)
# include_directories(${PROTOBUF_INCLUDE_DIRS})
# list(APPEND libs ${PROTOBUF_LIBRARIES})

# set(PROTO_LIST
# 	game_event
# 	grSim_Commands
# 	grSimMessage
# 	grSim_Packet
# 	grSim_Replacement
# 	messages_robocup_ssl_detection
# 	messages_robocup_ssl_geometry_legacy
# 	messages_robocup_ssl_geometry
# 	messages_robocup_ssl_refbox_log
# 	messages_robocup_ssl_wrapper_legacy
# 	messages_robocup_ssl_wrapper
# 	referee
# 	vision_detection
# 	zss_cmd
# 	zss_debug
# )
# get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

set(PROJECT_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
)
include_directories(${PROJECT_INCLUDE_DIRS})

# file(GLOB CPPFILES 
# 	"${CMAKE_SOURCE_DIR}/Utils/*.cpp"
# )

set(EXPORT_HEADERS
	udpsender.h
)
set(HEADERS
	${EXPORT_HEADERS}
)
set(SOURCES
	udpsender.cpp
)
set(SRC
	${HEADERS}
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
	${CPPFILES}
)

set(target_lib zss_udpsender)
execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
list(INSERT CMAKE_MODULE_PATH 0 ${CPYY_MODULE_PATH})
find_package(Cppyy)

add_library(${target_lib} SHARED ${SRC})

set_target_properties(${target_lib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${target_lib} PUBLIC ${PROJECT_INCLUDE_DIRS})

cppyy_add_bindings(
   "${target_lib}" "0.0.1" "ZJUNlict" "zjunlict.ssl@gmail.com"
   LANGUAGE_STANDARD "17"
   GENERATE_OPTIONS "-D__PIC__;-Wno-macro-redefined"
   INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS}
   LINK_LIBRARIES ${target_lib}
   H_DIRS ${PROJECT_INCLUDE_DIRS}
   H_FILES ${EXPORT_HEADERS})

target_link_libraries(${target_lib} ${libs})

install(TARGETS ${target_lib}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)