ADD_EXECUTABLE(read-w1-sensor read-w1-sensor.cpp)
TARGET_LINK_LIBRARIES(read-w1-sensor company)

ADD_EXECUTABLE(set-sysfs-gpio-switch set-sysfs-gpio-switch.cpp)
TARGET_LINK_LIBRARIES(set-sysfs-gpio-switch company)
