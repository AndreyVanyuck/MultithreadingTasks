//#include "Queue.cpp"
//
//class FixedAtomicQueue : public Queue {
//private:
//    atomic<uint8_t>* queue;
//    size_t size_;
//    atomic<int> pushIndex, popIndex;
//
//public:
//    FixedAtomicQueue(size_t s) {
//        pushIndex = 0;
//        popIndex = 0;
//        size_ = s;
//        queue = new atomic<uint8_t>[size_];
//        for (int i = 0; i < size_; i++)
//            queue[i] = 0;
//    }
//
//    void push(uint8_t val) override {
//        while (true) {
//            int currentPushIndex = pushIndex.load();
//            if (currentPushIndex == popIndex.load() + size_) {
//                continue;
//            }
//
//            byte x = q[currentPushIndex % size];
//            if (x != 0) continue;
//
//            if (pushIndex.compare_exchange_strong(currentPushIndex,
//                currentPushIndex + 1)) {
//                if (q[currentPushIndex % size].compare_exchange_strong(x, val))
//                    return;
//            }
//        }
//    }
//
//    bool pop(byte& val) override {
//        int currentPopIndex = popIndex.load();
//        if (currentPopIndex == pushIndex.load()) {
//            return false;
//        }
//
//        byte x = q[currentPopIndex % size];
//        if (x == 0) return false;
//        if (popIndex.compare_exchange_strong(currentPopIndex,
//            currentPopIndex + 1)) {
//
//            if (q[currentPopIndex % size].compare_exchange_strong(x, 0)) {
//                val = x;
//                return true;
//            }
//        }
//        return false;
//    }
//
//    string to_string() override {
//        return "FixedAtomicQueue";
//    }
//};
//#include <thread>
//#include <mutex>
//#include <atomic>
//#include <chrono>
//#include <condition_variable>
#include "Queue.cpp"


class FixedAtomicQueue : public Queue
{
    const size_t size;
    std::atomic<size_t> head, tail;
    std::atomic<bool> isbusy_push, isbusy_pop;
    std::vector<uint8_t> q;

public:
    FixedAtomicQueue(size_t size) : size(size), head(0), tail(0), isbusy_push(false), isbusy_pop(false)
    {
        q.resize(size);
    }

    void push(uint8_t val) override
    {
        while (true)
        {
            size_t curr_tail = tail.load();
            if (curr_tail == head + size) 
                continue;                    // check overflow
            uint8_t x = q[curr_tail % size];
            if (curr_tail != tail || x != 0) 
                continue;
            if (tail.compare_exchange_strong(curr_tail, curr_tail + 1))
            {
                q[curr_tail % size] = val;
                return;
            }
        }
    }

    bool pop(uint8_t& val) override
    {
        while (true)
        {
            size_t curr_head = head.load();
            // empty
            if (curr_head == tail)
            {
                this_thread::sleep_for(chrono::milliseconds(1));
                curr_head = head.load();
                if (curr_head == tail)
                    return false;
            }
            uint8_t x = q[curr_head % size];
            if (curr_head != head || x == 0)
                continue;
            if (head.compare_exchange_strong(curr_head, curr_head + 1))
            {
                val = x;
                q[curr_head % size] = 0;
                return true;
            }
        }
    }

    string to_string() override {
        return "FixedAtomicQueue ";
    }
};