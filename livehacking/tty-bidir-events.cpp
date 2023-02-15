#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <assert.h>

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << "<device> <sent-content>" << endl;
        return 1;
    }

    string device = argv[1];
    string sent_content = argv[2];
    sent_content += '\n';

    int fd = open(device.c_str(), O_RDWR);
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
        fd_set input, output;
        FD_ZERO(&input);
        FD_ZERO(&output);
        FD_SET(fd, &input);
        FD_SET(fd, &output);

        int nready = select(fd+1, &input, &output, nullptr, nullptr);
        if (nready == -1) {
            perror("select");
            return 1;
        }
        assert(nready > 0);

        if (FD_ISSET(fd, &input)) {
            char buf[16];
            ssize_t nread = read(fd, buf, sizeof(buf));
            if (nread == -1) {
                perror("reader: read");
                exit(1);
            }
            ssize_t nwritten = write(STDOUT_FILENO, buf, nread);
            if (nwritten == -1) {
                perror("reader: write");
                exit(1);
            }
        }

        if (FD_ISSET(fd, &output)) {
            ssize_t nwritten = write(fd, sent_content.c_str(), sent_content.size());
            if (nwritten == -1) {
                perror("writer: write");
                exit(1);
            }
        }
    }

    return 0;
}
