#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

const int bufferSize = 10;
int buffer[bufferSize];
int cnt = 0;

void producer() {
    while(true) {
        std::unique_lock<mutex> lock(mtx);
        if(cnt == bufferSize) {
            cout<<"Buffer is full !!!"<<endl;
            cv.wait(lock);
        }

        buffer[cnt++] = cnt;
        cout<<"Producing item : "<<buffer[cnt-1]<<endl;
        cv.notify_one();
    }
}

void consumer() {
    while(true) {
        std::unique_lock<mutex> lock(mtx);
        if(cnt == 0) {
            cout<<"Buffer is empty !!!"<<endl;
            cv.wait(lock);
        }

        cnt--;
        cout<<"Consumed item : "<<buffer[cnt]<<endl;
        cv.notify_one();
    }
}

int main() {

    thread P(producer);
    thread C(consumer);

    P.join();
    C.join();

    return 0;
}
