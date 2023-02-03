ADD_EXECUTABLE(hello hello.cpp)

# cross tests, from
# https://www.faschingbauer.me/blog/2022/09/cross-raspi.html
ADD_EXECUTABLE(c-stdio c-stdio.c)
ADD_EXECUTABLE(c++-iostream c++-iostream.cpp)
ADD_EXECUTABLE(c++-thread c++-thread.cpp)
TARGET_LINK_LIBRARIES(c++-thread Threads::Threads)
