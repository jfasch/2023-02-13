ADD_LIBRARY(
  company

  sensor-w1.h
  sensor-w1.cpp

  switch-sysfsgpio.h
  switch-sysfsgpio.cpp
)  

TARGET_INCLUDE_DIRECTORIES(
  company
  
  PUBLIC
  .
  )
