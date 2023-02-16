#include "sensor-lm73.h"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <sstream>
using namespace std;

LM73Sensor::LM73Sensor(int bus, int address)
{
    ostringstream buspath;
    buspath << "/dev/i2c-" << bus << ends;
    string buspath_s = buspath.str();

    _bus_fd = open(buspath_s.c_str(), O_RDWR);
    if (_bus_fd == -1) {
        ostringstream msg;
        msg << "cannot open bus " << buspath_s << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }

    if (ioctl(_bus_fd, I2C_SLAVE, address) == -1) {
        ostringstream msg;
        msg << "cannot set address 0x" << hex << address << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }
}

LM73Sensor::~LM73Sensor()
{
    if (_bus_fd != -1)
        close(_bus_fd);
}

double LM73Sensor::get_temperature()
{
    /* set register address for next read operation */
    uint8_t byte = 0x0;
    ssize_t nwritten = write(_bus_fd, &byte, 1);
    if (nwritten == -1) {
        ostringstream msg;
        msg << "write: " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }
    assert(nwritten == 1);

    /* read temperature */
    uint8_t msb_lsb[2];
    ssize_t nread = read(_bus_fd, msb_lsb, 2);
    if (nread == -1) {
        ostringstream msg;
        msg << "read: " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }
    assert(nread == 2);

    return (double)((msb_lsb[0]<<24)|(msb_lsb[1]<<16)) / 65535 / 128;
}
