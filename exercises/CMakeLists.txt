ADD_EXECUTABLE(
  mycat-joerg.faschingbauer
  mycat-joerg.faschingbauer.cpp
  )








ADD_EXECUTABLE(
  exercises-suite

  fail.cpp
  )

TARGET_LINK_LIBRARIES(
  exercises-suite

  gtest_main 
  )
