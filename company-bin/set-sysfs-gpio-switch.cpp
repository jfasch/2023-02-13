#include <switch-sysfsgpio.h>

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
    int gpionum = stoi(argv[1]);
    int state = stoi(argv[2]);

    SysFSGPIOSwitch led(gpionum);
    led.export_init();
    led.set_state(state);
    led.unexport_deinit();
    return 0;
}
