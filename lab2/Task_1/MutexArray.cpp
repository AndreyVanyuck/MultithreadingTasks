#include "BaseArray.cpp"
#include <mutex>

class MutexArray : public BaseArray {
private:
    int index;
    std::mutex mutex;

public: 
    MutexArray() : BaseArray() {
        index = 0;
    }

    void increment() override {
        while (true) {
            mutex.lock();
            int cur_index = index;
            index++;
            mutex.unlock();
            if (cur_index < NumTasks) {
                byte_arr[cur_index] ++;
                this_thread::sleep_for(chrono::nanoseconds(10));
            }
            else {
                break;
            }
        }
    }
};
