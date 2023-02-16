#include "display-pwm.h"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sstream>
using namespace std;


PWMDisplay::PWMDisplay(const std::string& sysfsdir)
: _period(sysfsdir + "/period"),
  _duty_cycle(sysfsdir + "/duty_cycle")
{
    int perfd = open(_period.c_str(), O_WRONLY);
    if (perfd == -1) {
        ostringstream msg;
        msg << "cannot open period " << _period << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }

    static const char one_million[] = "1000000";
    ssize_t nwritten = write(perfd, one_million, sizeof(one_million));
    if (nwritten == -1) {
        close(perfd);
        ostringstream msg;
        msg << "write period " << _period << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }

    close(perfd);
}

void PWMDisplay::show_temperature(double temperature)
{
    if (temperature > 40)
        temperature = 40;

    int dutyfd = open(_duty_cycle.c_str(), O_WRONLY);
    if (dutyfd == -1) {
        ostringstream msg;
        msg << "cannot open duty_cycle " << _duty_cycle << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }

    uint64_t duty_cycle = temperature / 40 * 1000000;

    ostringstream period_s;
    period_s << duty_cycle << ends;
    string period_str = period_s.str();

    ssize_t nwritten = write(dutyfd, period_str.c_str(), period_str.size());
    if (nwritten == -1) {
        close(dutyfd);
        ostringstream msg;
        msg << "write duty_cycle " << _duty_cycle << ": " << strerror(errno) << ends;
        throw runtime_error(msg.str().c_str());
    }

    close(dutyfd);
}




