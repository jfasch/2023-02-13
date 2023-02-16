ADD_LIBRARY(
  company

  sensor-w1.h
  sensor-w1.cpp

  sensor-lm73.h
  sensor-lm73.cpp

  switch-sysfsgpio.h
  switch-sysfsgpio.cpp

  display-pwm.h
  display-pwm.cpp
)  

TARGET_INCLUDE_DIRECTORIES(
  company
  
  PUBLIC
  .
  )
