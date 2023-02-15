#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>
using namespace std;


int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " FILENAME" << endl;
        return 1;
    }

    string filename = argv[1];
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (true) {
        char buf[16];
        ssize_t n_bytes_read = read(fd, buf, sizeof(buf));
        if (n_bytes_read == -1) {
            perror("read");
            return 2;
        }

        if (n_bytes_read == 0) // EOF
            break;

        ssize_t n_bytes_written = write(STDOUT_FILENO, buf, n_bytes_read);
        if (n_bytes_written == -1) {
            perror("write");
            return 3;
        }
    }

    close(fd);
    return 0;
}
