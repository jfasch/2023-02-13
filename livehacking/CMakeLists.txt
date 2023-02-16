ADD_EXECUTABLE(hello hello.cpp)

# cross tests, from
# https://www.faschingbauer.me/blog/2022/09/cross-raspi.html
ADD_EXECUTABLE(c-stdio c-stdio.c)
ADD_EXECUTABLE(c++-iostream c++-iostream.cpp)
ADD_EXECUTABLE(c++-thread c++-thread.cpp)
TARGET_LINK_LIBRARIES(c++-thread Threads::Threads)

ADD_EXECUTABLE(race-condition race-condition.cpp)
TARGET_LINK_LIBRARIES(race-condition Threads::Threads)

ADD_EXECUTABLE(tty-write tty-write.cpp)
ADD_EXECUTABLE(tty-read tty-read.cpp)
ADD_EXECUTABLE(tty-bidir-threads tty-bidir-threads.cpp)
TARGET_LINK_LIBRARIES(tty-bidir-threads Threads::Threads)
ADD_EXECUTABLE(tty-bidir-events tty-bidir-events.cpp)

ADD_EXECUTABLE(LM73 LM73.cpp)

ADD_EXECUTABLE(can-sensor can-sensor.cpp)
ADD_EXECUTABLE(can-display can-display.cpp)

ADD_EXECUTABLE(little-endian little-endian.cpp)
