#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

const int bufferSize = 10;
int buffer[bufferSize];
int cnt = 0;

void producer() {
    while(true) {
        if(cnt == bufferSize) {
            cout<<"Buffer is full !!!"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            continue;
        }

        mtx.lock();
        buffer[cnt++] = cnt;
        cout<<"Producing item : "<<buffer[cnt-1]<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        mtx.unlock();
    }
}

void consumer() {
    while(true) {
        if(cnt == 0) {
            cout<<"Buffer is empty !!!"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            continue;
        }

        mtx.lock();
        cnt--;
        cout<<"Consumed item : "<<buffer[cnt]<<endl;
        mtx.unlock();
    }
}

int main() {

    thread P(producer);
    thread C(consumer);

    P.join();
    C.join();

    return 0;
}