#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <queue>

using namespace std;

class Queue {
public:
    virtual void push(uint8_t val) = 0;
    virtual bool pop(uint8_t& val) = 0;
};
