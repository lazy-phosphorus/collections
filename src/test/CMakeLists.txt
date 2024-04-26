set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

message(STATUS "Clean test binary directory")
file(GLOB files ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
foreach(file_path ${files})
    file(REMOVE ${file_path})
endforeach()

file(GLOB files ${SOURCE_DIR}/*.c)
foreach(file_path ${files})
    get_filename_component(file_name ${file_path} NAME_WLE)
    add_executable(${file_name} ${file_path})
    target_link_libraries(${file_name} PRIVATE lib${file_name}.a)
    add_test(NAME ${file_name} COMMAND ${file_name})
endforeach()