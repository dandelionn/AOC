# Include Google Test into the build process
set( GTEST_DIR "gtest-1.8.1")
add_subdirectory( ${GTEST_DIR} )

# Include Google Test into Externals group
set_target_properties( gtest gtest_main gmock gmock_main PROPERTIES FOLDER "extra/externals/Google Test" )

if( WIN32 ) # windows
    set_property(TARGET gtest PROPERTY COMPILE_FLAGS /W0)
else() # other platforms
    set_property(TARGET gtest PROPERTY COMPILE_FLAGS -w)
endif()

# Export GMock headers
# Export GTest headers
include_directories("${GTEST_DIR}/googletest/include"
                    "${GTEST_DIR}/googlemock/include")