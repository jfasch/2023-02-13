#include <display-pwm.h>

#include <time.h>

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.14159265359;
const unsigned NSTEPS = 100;

int main(int argc, char** argv)
{
    timespec gap = {0, 10*1000*1000};

    while (true) {
        double x = 0;
        for (unsigned i=0; i<NSTEPS; i++) {
            double f = sin(x);
            cout << f << endl;
            x += 2*PI/NSTEPS;
            nanosleep(&gap, nullptr);
        }
    }

    return 0;
}
