cmake_minimum_required(VERSION 3.0)

set(project_name flow_and_preflow_algorithms)

project(${project_name})

message("Generation solution ${project_name}.")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Building for linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("Building for windows")
    if( MSVC )
        message("Selected generator: Microsoft Visual Studio ")
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
        set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "extra/tools/build")
    endif()
else()
    message(FATAL_ERROR "System ${CMAKE_SYSTEM_NAME} is not supported")
endif()

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
    endif()
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON) #this ensures c++17 is used
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

option(ENABLE_GTEST "Enable Google Tests for unit tests" OFF)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

message("Solution's top level directory: ${CMAKE_SOURCE_DIR}")
message("Sources directory:              ${CMAKE_SOURCE_DIR}/source")
message("Build directory:                ${CMAKE_BINARY_DIR}")
message("Static libraries directory:     ${LIBRARY_OUTPUT_PATH}")
message("Executables directory:          ${EXECUTABLE_OUTPUT_PATH}")
message("Build unit tests:               ${ENABLE_GTEST}")

add_subdirectory(source/flow_algorithms)
add_subdirectory(source/preflow_algorithms)
add_subdirectory(source/common)
add_subdirectory(source/app)

if(ENABLE_GTEST)
    enable_testing()
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is build as static lib." FORCE)
    endif()
    add_subdirectory(externals)
    add_subdirectory(test/flow_algorithms_test/unit)
	add_subdirectory(test/preflow_algorithms_test/unit)
endif()
