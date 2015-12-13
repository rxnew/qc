cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(TARGET qc)

set(FILE_LIST bit gate step circuit)

set(LIB_LIST ddmf clique-and-vertex-color)

set(SOURCE_LIST)

foreach(FILE_NAME ${FILE_LIST})
  list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/${FILE_NAME}.cpp)
endforeach(FILE_NAME)

add_library(${TARGET} STATIC ${SOURCE_LIST})

target_link_libraries(${TARGET} ${LIB_LIST})

add_definitions("-std=c++11")
