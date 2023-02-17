#pragma once

#include "display.h" 

#include <string>

class CANDisplay : public Display
{
public:
    CANDisplay(unsigned id, const std::string& iface);
    void show_temperature(double temperature);

private:
    int _id;
    int _can_socket;
};
