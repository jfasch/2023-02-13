#include <sensor-lm73.h>

#include <iostream>
#include <string>
using namespace std;


int main(int argc, char** argv)
{
    LM73Sensor sensor(stoi(argv[1]), stoi(argv[2], nullptr, 16));
    cout << sensor.get_temperature() << endl;

    return 0;
}
