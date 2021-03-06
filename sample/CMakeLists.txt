cmake_minimum_required(VERSION 3.2)

project(sample CXX)

set(TARGETS main)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/external_projects.cmake)

include_directories(${EXTERNAL_PROJECTS_INCLUDE_PATHS})

foreach(TARGET ${TARGETS})
  add_executable(${TARGET} ${SOURCE_DIR}/${TARGET}.cpp)
  target_link_libraries(${TARGET} ${EXTERNAL_PROJECTS_LIBRARIES})
  if(BUILD_EXTERNAL_PROJECT_NAMES)
    add_dependencies(${TARGET} ${BUILD_EXTERNAL_PROJECT_NAMES})
  endif()
endforeach(TARGET)

#add_custom_target(reload ALL
#                  COMMAND cmake ${CMAKE_CURRENT_SOURCE_DIR}
#                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#                  DEPENDS ${TARGETS})

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")
