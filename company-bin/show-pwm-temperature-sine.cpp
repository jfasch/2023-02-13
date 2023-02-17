#include <display-pwm.h>

#include <time.h>
#include <unistd.h>
#include <string.h>

// realtime section :-)
#include <sched.h>
#include <sys/mman.h>

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.14159265359;
const unsigned NSTEPS = 100;

void show_value(double v)
{
    for (int i=0; i<(int)v; i++)
        cout << '*';
    cout << endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <PWM-DIR>" << endl;
        return 1;
    }
    PWMDisplay display(argv[1], 0, 40);

    timespec gap = {0, 10*1000*1000};

    pid_t myself = getpid();
    if (myself == 0) {   // root does realtime
        int error;

        error = mlockall(MCL_CURRENT|MCL_FUTURE);
        if (error == -1) {
            perror("mlockall");
            return 1;
        }
        
        sched_param param;
        memset(&param, 0, sizeof(param));
        param.sched_priority = 2;

        error = sched_setscheduler(myself, SCHED_FIFO, &param);
        if (error == -1) {
            perror("sched_setscheduler");
            return 1;
        }
    }

    while (true) {
        double x = 0;
        for (unsigned i=0; i<NSTEPS; i++) {
            double f = sin(x)*20+20;
            //cout << f << endl;
            //show_value(f);
            display.show_temperature(f);
            x += 2*PI/NSTEPS;
            nanosleep(&gap, nullptr);
        }
    }

    return 0;
}
