# DecisionModule
set(libs)

set(USE_PYTHON_MODULE false)
set(USE_CUDA_MODULE false)
if(USE_PYTHON_MODULE)
	add_definitions(-DUSE_PYTHON_MODULE)
endif()
if(USE_CUDA_MODULE)
	add_definitions(-DUSE_CUDA_MODULE)
endif()

# lua51
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
list(APPEND libs ${LUA_LIBRARIES})

# tolua++
find_package(toluapp REQUIRED)
include_directories(${TOLUAPP_INCLUDE_DIR})
list(APPEND libs ${TOLUAPP_LIBRARIES})

# CUDA
if(USE_CUDA_MODULE)
	find_package(CUDA REQUIRED)
	include_directories(${CUDA_INCLUDE_DIRS})
	list(APPEND libs ${CUDA_LIBRARIES})
endif()

# Qt5
find_package(Qt5 COMPONENTS Core Network REQUIRED)
list(APPEND libs Qt5::Core Qt5::Network)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
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

set(PROJECT_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
	${CMAKE_CURRENT_SOURCE_DIR}/Algorithm
	${CMAKE_CURRENT_SOURCE_DIR}/CUDAModule
	${CMAKE_CURRENT_SOURCE_DIR}/LuaModule
	${CMAKE_CURRENT_SOURCE_DIR}/MotionControl
	${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs
	${CMAKE_CURRENT_SOURCE_DIR}/PathPlan
	${CMAKE_CURRENT_SOURCE_DIR}/PointCalculation
	${CMAKE_CURRENT_SOURCE_DIR}/PythonModule
	${CMAKE_CURRENT_SOURCE_DIR}/RefereeBox
	${CMAKE_CURRENT_SOURCE_DIR}/Simulator
	${CMAKE_CURRENT_SOURCE_DIR}/Strategy
	${CMAKE_CURRENT_SOURCE_DIR}/Utils
	${CMAKE_CURRENT_SOURCE_DIR}/Vision
	${CMAKE_CURRENT_SOURCE_DIR}/Wireless
	${CMAKE_CURRENT_SOURCE_DIR}/WorldModel

	${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/cmu
	${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/cornell
	${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/nlopt
	${CMAKE_CURRENT_SOURCE_DIR}/Strategy/bayes
	${CMAKE_CURRENT_SOURCE_DIR}/Strategy/defence
	${CMAKE_CURRENT_SOURCE_DIR}/Strategy/rolematch
	${CMAKE_CURRENT_SOURCE_DIR}/Strategy/skill
	${CMAKE_CURRENT_SOURCE_DIR}/Vision/mediator/net
)
include_directories(${PROJECT_INCLUDE_DIRS})

file(GLOB CPPFILES 
	"${CMAKE_SOURCE_DIR}/Utils/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/CUDAModule/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/LuaModule/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/MotionControl/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/PathPlan/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/PointCalculation/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/PythonModule/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/RefereeBox/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Simulator/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Strategy/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Vision/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Wireless/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/WorldModel/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/cmu/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/cornell/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/OtherLibs/nlopt/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Strategy/bayes/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Strategy/defence/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Strategy/rolematch/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Strategy/skill/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Vision/mediator/net/*.cpp"
)

set(EXPORT_HEADERS
	decisionmodule.h
)
set(HEADERS
	${EXPORT_HEADERS}
)
set(SOURCES
	decisionmodule.cpp
)
set(SRC
	${HEADERS}
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
	${CPPFILES}
)

set(target_lib zss_decision)

if(BUILD_PYTHON_PLUGINS)
	execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
	list(INSERT CMAKE_MODULE_PATH 0 ${CPYY_MODULE_PATH})
	find_package(Cppyy)
endif()

add_library(${target_lib} SHARED ${SRC})

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