cmake_minimum_required(VERSION 2.8)

add_executable(gate-test x_test.cpp group_test.cpp)
target_link_libraries(gate-test
  gtest
  gtest_main
  pthread
  qc
  )

add_test(
  NAME gate
  COMMAND $<TARGET_FILE:gate-test>
  )

# run with: ctest -L lib
set_property(
  TEST gate
  PROPERTY LABELS lib gate
  )
