# Metadata
cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)

# Project infos
project(collections LANGUAGES C)

# Project settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Path settings
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_HEADER_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include settings
include_directories(${SOURCE_DIR} ${SOURCE_DIR}/basic ${SOURCE_DIR}/advanced)

# Clean cache
message(STATUS "Clean header output directory")
file(GLOB files ${CMAKE_HEADER_OUTPUT_DIRECTORY}/*)
foreach(file_path ${files})
    file(REMOVE ${file_path})
    endforeach()
message(STATUS "Clean library output directory")
file(GLOB files ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/*)
foreach(file_path ${files})
    file(REMOVE ${file_path})
endforeach()

# Generate libraries
aux_source_directory(${SOURCE_DIR}/basic basic)
aux_source_directory(${SOURCE_DIR}/advanced advanced)
add_library(collections_static STATIC ${basic} ${advanced})
set_target_properties(collections_static PROPERTIES OUTPUT_NAME collections)
set_target_properties(collections_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
add_library(collections_dynamic SHARED ${basic} ${advanced})
set_target_properties(collections_dynamic PROPERTIES OUTPUT_NAME collections)
set_target_properties(collections_dynamic PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Copy headers
file(GLOB headers ${SOURCE_DIR}/basic/*.h)
foreach(header ${headers})
    file(COPY ${header} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/collections)
endforeach()
file(GLOB headers ${SOURCE_DIR}/advanced/*.h)
foreach(header ${headers})
    file(COPY ${header} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/collections)
endforeach()
file(GLOB headers ${SOURCE_DIR}/*.h)
foreach(header ${headers})
    file(COPY ${header} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/collections)
endforeach()

# Unit test
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

