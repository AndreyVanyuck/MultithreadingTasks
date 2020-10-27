#pragma once
#include <chrono>
#include <thread>

using namespace std;

class BaseArray {
protected:
    const int NumTasks = 1024 * 1024;
    uint8_t* byte_arr;

public:
    BaseArray() {
        byte_arr = new uint8_t[NumTasks];
        for (int i = 0; i < NumTasks; i++)
            byte_arr[i] = 0;
    }

    virtual void increment() = 0;

    ~BaseArray() {
        delete[] byte_arr;
    }
};
