#include <linux/can.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>

#include <string>
#include <iostream>
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
    while (true) {
        ssize_t nread = read(s, &frame, sizeof(frame));
        if (nread == -1) {
            perror("read");
            return 1;
        }

        cout << "ID: " << frame.can_id << endl;
        cout << "DLC: " << (uint32_t)frame.can_dlc << endl;
        for (int i=0; i<8; i++)
            cout << "DATA[" << i << "]: 0x" << hex << (uint32_t)frame.data[i] << endl;
    }

    return 0;
}
