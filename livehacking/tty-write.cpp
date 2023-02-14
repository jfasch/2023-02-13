#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
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

    int fd = open(device.c_str(), O_WRONLY);
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
        ssize_t nwritten = write(fd, sent_content.c_str(), sent_content.size());
        if (nwritten == -1) {
            perror("write");
            exit(1);
        }
    }

    return 0;
}
