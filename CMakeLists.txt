cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/util)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(TARGET qc)

set(UTIL_FILE_LIST container_helper string_helper)

set(QC_FILE_LIST bit gate circuit)

set(SOURCE_LIST)

foreach(FILE_NAME ${UTIL_FILE_LIST})
  list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/util/${FILE_NAME}.cpp)
endforeach(FILE_NAME)

foreach(FILE_NAME ${QC_FILE_LIST})
  list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/qc/${FILE_NAME}.cpp)
endforeach(FILE_NAME)

add_library(${TARGET} STATIC ${SOURCE_LIST})

add_definitions("-std=c++11 -Wall")
