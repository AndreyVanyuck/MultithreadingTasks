#include <iostream>
#include <cassert>

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

    void print() {
        for (int i = 0; i < NumTasks; i++)
            std::cout << static_cast<int>(byte_arr[i]) << " ";
            //std::cout << byte_arr[i] << " ";
    }

    //void init() {
    //    byte_arr = new uint8_t[NumTasks];
    //    for (int i = 0; i < NumTasks; i++)
    //        byte_arr[i] = 0;
    //}

    void check() {
        for (int i = 0; i < NumTasks; i++)
            assert(byte_arr[i] == 1);
     //   print();
    }

  /*  virtual void init() = 0;*/
    virtual void increment() = 0;

    ~BaseArray() {
        delete[] byte_arr;
    }
};
