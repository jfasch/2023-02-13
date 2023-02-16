#pragma once

#include <string>

class PWMDisplay
{
public:
    PWMDisplay(const std::string& sysfsdir);
    void show_temperature(double temperature);

private:
    std::string _period;
    std::string _duty_cycle;
};
