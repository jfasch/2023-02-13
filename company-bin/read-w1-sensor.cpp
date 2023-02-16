#include <sensor-w1.h>

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
    W1Sensor sensor(argv[1]);
    cout << sensor.get_temperature() << endl;

    return 0;
}
