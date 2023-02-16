#pragma once

#include <string>


class W1Sensor
{
public:
    W1Sensor(const std::string& filename);
    double get_temperature();

private:
    const std::string _filename;
};
