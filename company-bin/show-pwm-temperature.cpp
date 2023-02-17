#include <display-pwm.h>

#include <string>
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <PWM-DIR> <CELSIUS>" << endl;
        return 1;
    }

    string pwmdir = argv[1];
    double temperature = stod(argv[2]);

    PWMDisplay display(pwmdir, 0, 40);

    cout << "period: " << display.period_file() << endl;
    cout << "duty_cycle: " << display.duty_cycle_file() << endl;
    cout << "temperature: " << temperature << endl;

    display.show_temperature(temperature);

    return 0;
}
