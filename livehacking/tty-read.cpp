#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <sys/ioctl.h>

#include <iostream>
#include <thread>
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << "<device>" << endl;
        return 1;
    }

    string device = argv[1];

    int fd = open(device.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // stty -F /dev/ttyUSB0 -cooked
    {
        termios settings;
        int error = tcgetattr(fd, &settings);
        if (error) {
            perror("tcgetattr");
            return 1;
        }
        cfmakeraw(&settings);
        error = tcsetattr(fd, TCSADRAIN, &settings);
        if (error) {
            perror("tcsetattr");
            return 1;
        }
    }

    // setserial /dev/ttyUSB0 low_latency
    {
        serial_struct serinfo;
        int error = ioctl(fd, TIOCGSERIAL, &serinfo);
        if (error == -1) {
            perror("ioctl(TIOCGSERIAL)");
            return 1;
        }

        serinfo.flags |= ASYNC_LOW_LATENCY;

        error = ioctl(fd, TIOCSSERIAL, &serinfo);
        if (error == -1) {
            perror("ioctl(TIOCSSERIAL)");
            return 1;
        }
    }

    while (true) {
        char buf[16];
        ssize_t nread = read(fd, buf, sizeof(buf));
        if (nread == -1) {
            perror("read");
            exit(1);
        }
        ssize_t nwritten = write(STDOUT_FILENO, buf, nread);
        if (nwritten == -1) {
            perror("write");
            exit(1);
        }
    }

    return 0;
}
