message( "Generating unit tests for flow_algorithms" )
project(flow_algorithms-utest)

set(
    source_files
    src/main.cpp
	src/maximum_capacity_scaling_ahuja_orlin_test.cpp
	src/shortest_path_ahuja_orlin_test.cpp
	src/edmonds_karp_test.cpp
)

link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(${PROJECT_NAME} ${source_files})

# Add to Ctests
add_test(NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
        WORKING_DIRECTORY ${ATM_BIN_DIR})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "test")
endif()

target_link_libraries(${PROJECT_NAME}
    flow_algorithms
    gtest gtest_main gmock gmock_main
)
