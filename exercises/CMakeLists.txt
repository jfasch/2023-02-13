ADD_EXECUTABLE(
  mycat
  mycat.cpp
  )



ADD_EXECUTABLE(
  exercises-suite

  fail.cpp
  )

TARGET_LINK_LIBRARIES(
  exercises-suite

  gtest_main 
  )
