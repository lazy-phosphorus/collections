# Test settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Test include and library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../src/basic ${CMAKE_CURRENT_SOURCE_DIR}/../src/advanced ${SOURCE_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# Clean Test cache
message(STATUS "Clean test binary directory")
file(GLOB files ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
foreach(file_path ${files})
    file(REMOVE ${file_path})
endforeach()

# Build unit test cases.
file(GLOB dirs ${SOURCE_DIR}/*)
foreach(dir_path ${dirs})
    get_filename_component(dir_name ${dir_path} NAME_WLE)
    file(GLOB files ${dir_path}/*.c)
    foreach(file_path ${files})
        get_filename_component(file_name ${file_path} NAME_WLE)
        add_executable(${dir_name}-${file_name} ${file_path})
        target_link_libraries(${dir_name}-${file_name} PRIVATE libcollections.so)
        add_test(NAME ${dir_name}/${file_name} COMMAND ${dir_name}-${file_name})
    endforeach()
endforeach()