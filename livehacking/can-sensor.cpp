#include <linux/can.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>
#include <unistd.h>

#include <string>
using namespace std;


int main(int argc, char** argv)
{
    string can_ifname = argv[1];

    int error;
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    // create socket, "attach" to bus/interface
    {
        s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

        strcpy(ifr.ifr_name, can_ifname.c_str());
        error = ioctl(s, SIOCGIFINDEX, &ifr);
        assert(!error);

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        error = bind(s, (struct sockaddr *)&addr, sizeof(addr));
        assert(!error);
    }

    can_frame frame;
    memset(&frame, 0, sizeof(frame));

    frame.can_id = 42;
    uint64_t milli_celsius = 666000;
    frame.can_dlc = 8;
    memcpy(&frame.data, &milli_celsius, 8);

    timespec delay = {0, 500*1000*1000};
    while (true) {
        ssize_t nwritten = write(s, &frame, sizeof(frame));    
        assert(nwritten == sizeof(frame));
        error = nanosleep(&delay, nullptr);
        assert(!error);
    }

    return 0;
}
