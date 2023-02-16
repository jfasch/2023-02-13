#pragma once


class SysFSGPIOSwitch
{
public:
    SysFSGPIOSwitch(int gpionum);
    
    void export_init();
    void unexport_deinit();

    void set_state(bool);
    bool get_state();

private:
    int _gpionum;
};
