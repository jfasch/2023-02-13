#pragma once

class LM73Sensor
{
public:
    LM73Sensor(int bus, int address);
    ~LM73Sensor();
    double get_temperature();

private:
    int _bus_fd;
};
