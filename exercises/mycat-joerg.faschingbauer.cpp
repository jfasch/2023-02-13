#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " FILENAME" << endl;
        return 1;
    }

    cerr << "Hier geschieht ein Wunder! " << argv[1] << endl;
    return 0;
}
