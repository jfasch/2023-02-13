#include <display-pwm.h>

#include <string>
using namespace std;


int main(int argc, char** argv)
{
    double temperature = stod(argv[2]);
    PWMDisplay display(argv[1]);

    display.show_temperature(temperature);

    return 0;
}
