set(libname flow_algorithms)

message("Generating ${libname} library")

# Project name
project(${libname})

set(header_files
	include/maximum_capacity_scaling_ahuja_orlin.hpp
	include/shortest_path_ahuja_orlin.hpp
	include/edmonds_karp.hpp
)

set(source_files
	src/maximum_capacity_scaling_ahuja_orlin.cpp
	src/shortest_path_ahuja_orlin.cpp
	src/edmonds_karp.cpp
)

# Generate static library
add_library(${libname} STATIC ${source_files} ${header_files})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "lib")
endif()


# Export include folder
target_include_directories(${libname} PUBLIC include/)