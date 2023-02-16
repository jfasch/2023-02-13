#include "switch-sysfsgpio.h"

#include <assert.h>


SysFSGPIOSwitch::SysFSGPIOSwitch(int gpionum)
: _gpionum(gpionum) {}
    
void SysFSGPIOSwitch::export_init()
{
    assert(!"hier noch brav sein");
}

void SysFSGPIOSwitch::unexport_deinit()
{
    assert(!"hier noch brav sein");
}

void SysFSGPIOSwitch::set_state(bool state)
{
    assert(!"hier noch brav sein");
}

bool SysFSGPIOSwitch::get_state()
{
    assert(!"hier noch brav sein");
}
