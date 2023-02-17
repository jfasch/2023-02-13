#include "display-can.h" 

#include <linux/can.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>
#include <unistd.h>

CANDisplay::CANDisplay(unsigned id, const std::string& iface)
: _id(id)
{
    int error;
    struct sockaddr_can addr;
    struct ifreq ifr;

    // create socket, "attach" to bus/interface
    _can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, iface.c_str());
    error = ioctl(_can_socket, SIOCGIFINDEX, &ifr);
    assert(!error);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    error = bind(_can_socket, (struct sockaddr *)&addr, sizeof(addr));
    assert(!error);
}

void CANDisplay::show_temperature(double temperature)
{
    can_frame frame;
    memset(&frame, 0, sizeof(frame));

    frame.can_id = _id;
    uint64_t milli_celsius = temperature * 1000;
    frame.can_dlc = 8;
    memcpy(&frame.data, &milli_celsius, 8);

    ssize_t nwritten = write(_can_socket, &frame, sizeof(frame));    
    assert(nwritten == sizeof(frame));
}
