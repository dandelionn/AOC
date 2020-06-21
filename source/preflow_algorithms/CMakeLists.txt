set(libname preflow_algorithms)

message("Generating ${libname} library")

# Project name
project(${libname})

set(header_files
	include/preflow_fifo.hpp
	include/preflow_with_biggest_label.hpp
	include/preflow_with_excess_scalling.hpp
)

set(source_files
	src/preflow_fifo.cpp
	src/preflow_with_biggest_label.cpp
	src/preflow_with_excess_scalling.cpp
)

# Generate static library
add_library(${libname} STATIC ${source_files} ${header_files})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "lib")
endif()


# Export include folder
target_include_directories(${libname} PUBLIC include/)