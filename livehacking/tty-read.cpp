#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>

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
