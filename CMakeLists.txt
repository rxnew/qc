cmake_minimum_required(VERSION 3.2)

project(qc CXX)

set(TARGET qc)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${TARGET} STATIC ${SOURCES})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_graph.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_json11.cmake)

include_directories(${GRAPH_INCLUDE_PATH})
include_directories(${JSON11_INCLUDE_PATH})

target_link_libraries(${TARGET} PUBLIC ${JSON11_LIBRARY})

install(TARGETS ${TARGET}
        EXPORT ${TARGET}-export
        ARCHIVE        DESTINATION lib
        INCLUDES       DESTINATION include)

install(DIRECTORY ${SOURCE_DIR}/
        DESTINATION include/${TARGET}
        FILES_MATCHING PATTERN *.hpp)

install(EXPORT ${TARGET}-export
        FILE ${TARGET}-config.cmake
        DESTINATION share/cmake/${TARGET}
        EXPORT_LINK_INTERFACE_LIBRARIES)

option(QC_BUILD_TESTS "Build unit tests" off)

if(QC_BUILD_TESTS)
  enable_testing()
  add_subdirectory(${TEST_DIR})
endif()

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")
