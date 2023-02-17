#pragma once

#include <string>

class PWMDisplay
{
public:
    PWMDisplay(const std::string& sysfsdir, double low, double high);
    void show_temperature(double temperature);

    const std::string& period_file() const { return _period; }
    const std::string& duty_cycle_file() const { return _duty_cycle; }

private:
    std::string _period;
    std::string _duty_cycle;

    const double _low;
    const double _high;
};
