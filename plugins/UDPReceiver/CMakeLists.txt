# UDPReceiver
set(libs)
# Qt5
find_package(Qt5 COMPONENTS Core Network REQUIRED)
list(APPEND libs Qt5::Core Qt5::Network)

set(PROJECT_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/proto
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Utils
	${CMAKE_SOURCE_DIR}/Utils/ZSPlugin
)
include_directories(${PROJECT_INCLUDE_DIRS})

set(EXPORT_HEADERS
	udpreceiver.h
)
set(HEADERS
	${EXPORT_HEADERS}
)
set(SOURCES
	udpreceiver.cpp
)
set(SRC
	${HEADERS}
	${SOURCES}
	${PROTO_CPP}
	${PROTO_H}
	${CPPFILES}
)

set(target_lib zss_udpreceiver)

# if(BUILD_PYTHON_PLUGINS)
# 	execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
# 	list(INSERT CMAKE_MODULE_PATH 0 ${CPYY_MODULE_PATH})
# 	find_package(Cppyy)
# endif()

add_library(${target_lib} SHARED ${SRC})

set_target_properties(${target_lib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${target_lib} PUBLIC ${PROJECT_INCLUDE_DIRS})

# if(BUILD_PYTHON_PLUGINS)
# 	cppyy_add_bindings(
# 	   "${target_lib}" "0.0.1" "ZJUNlict" "zjunlict.ssl@gmail.com"
# 	   LANGUAGE_STANDARD "17"
# 	   GENERATE_OPTIONS "-D__PIC__;-Wno-macro-redefined"
# 	   INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS}
# 	   LINK_LIBRARIES ${target_lib}
# 	   H_DIRS ${PROJECT_INCLUDE_DIRS}
# 	   H_FILES ${EXPORT_HEADERS})
# endif()

target_link_libraries(${target_lib} ${libs})

install(TARGETS ${target_lib}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)