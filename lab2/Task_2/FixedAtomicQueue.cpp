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