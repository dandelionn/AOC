message("Generating command line application")

# Project name
project(app)

set(source_files
    src/main.cpp
)

# Generate executable
add_executable(app ${source_files})

target_link_libraries(app flow_algorithms preflow_algorithms common)


#if(MSVC)
    # Include in solution group
#    set_property(TARGET app PROPERTY FOLDER "Modules/Applications")
#endif()