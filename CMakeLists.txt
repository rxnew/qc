cmake_minimum_required(VERSION 3.2)

project(qc CXX)

set(TARGET qc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/graph)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/json11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/graph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/json11)

set(LIBS ${CMAKE_CURRENT_BINARY_DIR}/lib/json11/libjson11.a)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${TARGET} STATIC ${SOURCES})

target_link_libraries(${TARGET} PUBLIC ${LIBS})

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
