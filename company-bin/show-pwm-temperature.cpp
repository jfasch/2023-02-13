#include <display-pwm.h>

#include <string>
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
    PWMDisplay display(argv[1], 0, 40);
    double temperature = stod(argv[2]);

    cout << "period: " << display.period_file() << endl;
    cout << "duty_cycle: " << display.duty_cycle_file() << endl;
    cout << "temperature: " << temperature << endl;

    display.show_temperature(temperature);

    return 0;
}
