#include "Queue.cpp"

class DynamicMutexQueue : public Queue {
private:
    queue<uint8_t> queue;
    mutex mutex;

public:
    void push(uint8_t val) override {
        mutex.lock();
        queue.push(val);
        mutex.unlock();
    }

    bool pop(uint8_t& val) override {
        mutex.lock();
        if (queue.empty()) {
            this_thread::sleep_for(chrono::milliseconds(1));
            mutex.unlock();
            return false;
        }
        val = queue.front();
        queue.pop();
        mutex.unlock();
        return true;
    }


    string to_string() override{
        return "DynamicMutexQueue ";
    }
};