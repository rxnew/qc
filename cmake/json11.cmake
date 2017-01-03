cmake_minimum_required(VERSION 2.8)

# json11 settings
include(ExternalProject)

ExternalProject_Add(
  json11
  GIT_REPOSITORY https://github.com/dropbox/json11.git
  GIT_TAG a501d06b98a5cd0cbe1ca1ea584adb4a5fbf2857
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/projects/json11
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )

ExternalProject_Get_Property(json11 source_dir)
ExternalProject_Get_Property(json11 binary_dir)

set(JSON11_INCLUDE_PATH ${source_dir})

add_library(libjson11 STATIC IMPORTED GLOBAL)

set_property(
  TARGET libjson11
  PROPERTY IMPORTED_LOCATION ${binary_dir}/libjson11.a
  )

set(JSON11_LIBRARY libjson11)
