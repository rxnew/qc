cmake_minimum_required(VERSION 2.8)

project(sample CXX)

set(MAIN main)
set(PACKAGE qc)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(${PACKAGE} REQUIRED CONFIG
             PATHS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(TARGET ${MAIN})
  add_executable(${TARGET} ${SOURCE_DIR}/${TARGET}.cpp)
  target_link_libraries(${TARGET} ${PACKAGE})
endforeach(TARGET)

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")
