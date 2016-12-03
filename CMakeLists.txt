cmake_minimum_required(VERSION 2.8)

project(qc CXX)

set(TARGET qc)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_library(${TARGET} STATIC ${SOURCES})

install(TARGETS ${TARGET}
        EXPORT ${TARGET}-export
        ARCHIVE        DESTINATION lib
        INCLUDES       DESTINATION include)

install(DIRECTORY ${SOURCE_DIR}/
        DESTINATION include/${TARGET}
        FILES_MATCHING PATTERN *.hpp)

install(DIRECTORY ${INCLUDE_DIR}/
        DESTINATION include)

install(EXPORT ${TARGET}-export
        FILE ${TARGET}-config.cmake
        DESTINATION share/cmake/${TARGET})

if(${TEST})
  enable_testing()
  add_subdirectory(${TEST_DIR})
endif()

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")
