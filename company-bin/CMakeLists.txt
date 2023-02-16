ADD_EXECUTABLE(read-w1-sensor read-w1-sensor.cpp)
TARGET_LINK_LIBRARIES(read-w1-sensor company)

ADD_EXECUTABLE(read-lm73-sensor read-lm73-sensor.cpp)
TARGET_LINK_LIBRARIES(read-lm73-sensor company)

ADD_EXECUTABLE(show-pwm-temperature show-pwm-temperature.cpp)
TARGET_LINK_LIBRARIES(show-pwm-temperature company)

ADD_EXECUTABLE(set-sysfs-gpio-switch set-sysfs-gpio-switch.cpp)
TARGET_LINK_LIBRARIES(set-sysfs-gpio-switch company)

ADD_EXECUTABLE(can-w1-sensor can-w1-sensor.cpp)
TARGET_LINK_LIBRARIES(can-w1-sensor company)

