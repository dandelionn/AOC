message( "Generating unit tests for preflow_algorithms" )
project(preflow_algorithms-utest)

set(
    source_files
    src/main.cpp
    src/preflow_fifo_test.cpp
    src/preflow_with_biggest_label_test.cpp
    src/preflow_with_excess_scalling_test.cpp
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
    preflow_algorithms
    gtest gtest_main gmock gmock_main
)
