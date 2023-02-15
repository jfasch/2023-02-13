#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
using namespace std;


//atomic<int> global_var;
mutex global_mutex;
int global_var;
int n_increments = 10*1000*1000;

void increment()
{
    for (int i=0; i<n_increments; i++) {
        global_mutex.lock();
        global_var++;
        global_mutex.unlock();
    }
}

int main()
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << global_var << endl;
    return 0;
}
