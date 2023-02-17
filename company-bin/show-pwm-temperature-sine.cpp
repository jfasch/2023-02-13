#include <display.h>
#include <display-pwm.h>
#include <display-can.h>

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

static int /*OS error*/ make_realtime()
{
    pid_t myself = getpid();
    if (myself == 0) {   // root does realtime
        int error;

        error = mlockall(MCL_CURRENT|MCL_FUTURE);
        if (error == -1) {
            perror("mlockall");
            return -1;
        }
        
        sched_param param;
        memset(&param, 0, sizeof(param));
        param.sched_priority = 2;

        error = sched_setscheduler(myself, SCHED_FIFO, &param);
        if (error == -1) {
            perror("sched_setscheduler");
            return -1;
        }
    }
    return 0;
}

class ConsoleDisplay : public Display
{
public:
    ConsoleDisplay(char c) : _c(c) {}
    void show_temperature(double t)
    {
        for (int i=0; i<(int)t; i++)
            cout << _c;
        cout << endl;
    }
private:
    char _c;
};

class NumbersDisplay : public Display
{
public:
    void show_temperature(double t)
    {
        cout << t << endl;
    }
};

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " {<PWM-DIR> | <CAN-IFACE> | console | numbers}" << endl;
        return 1;
    }

    string output = argv[1];

    Display* display;

    if (output == "console")
        display = new ConsoleDisplay('*');
    else if (output == "numbers")
        display = new NumbersDisplay();
    else if (output.find('/') != string::npos)
        display = new PWMDisplay(output, 0, 40);
    else 
        display = new CANDisplay(42, output);

    timespec gap = {0, 10*1000*1000};

    int error = make_realtime();
    if (error == -1) {
        perror("make_realtime");
        return 1;
    }

    while (true) {
        double x = 0;
        for (unsigned i=0; i<NSTEPS; i++) {
            double f = sin(x)*20+20;
            display->show_temperature(f);
            x += 2*PI/NSTEPS;
            nanosleep(&gap, nullptr);
        }
    }

    return 0;
}
