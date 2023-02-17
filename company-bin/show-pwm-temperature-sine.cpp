#include <display-pwm.h>

#include <time.h>

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double TWO_PI = 2*3.142;
const unsigned NSTEPS = 100;

int main(int argc, char** argv)
{
    timespec gap = {0, 10*1000*1000};

    while (true) {
        double x = 0;
        for (unsigned i=0; i<NSTEPS; i++) {
            double f = sin(x);
            cout << f << endl;
            x += TWO_PI/NSTEPS;
            nanosleep(&gap, nullptr);
        }
    }

    return 0;
}
