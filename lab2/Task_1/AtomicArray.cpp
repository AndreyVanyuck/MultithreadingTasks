#include "BaseArray.cpp"
#include <atomic>


class AtomicArray : public BaseArray {
private:
    atomic<int> index;

public:
    AtomicArray() : BaseArray() {
        index = 0;
    }

    void increment() override {
        while (true) {
            auto prev = index.fetch_add(1);
            if (prev >= NumTasks)
                break;
            byte_arr[prev]++;
            this_thread::sleep_for(chrono::nanoseconds(10));
        }
    }
};
