
#include "DynamicMutexQueue.cpp"
#include <cassert>
#include "FixedMutexQueue.cpp"

void startTask(Queue& q, int producerNum, int consumerNum, int taskNum) {
    atomic_int sum(0);
    vector<thread> producers(producerNum);
    vector<thread> consumers(consumerNum);

    auto producer = [&]() {
        for (int i = 0; i < taskNum; i++) {
            q.push(1);
        }
    };

    auto consumer = [&]() {
        int allTask = producerNum * taskNum;
        uint8_t val;
        while (sum.load() < allTask) {
            sum += q.pop(val);
        }
    };

    vector<thread> threads;;
    for (int i = 0; i < producerNum; i++) {
        threads.push_back(thread(producer));
    }
    for (int i = 0; i < consumerNum; i++) {
        threads.push_back(thread(consumer));
    }
    for (int i = 0; i < consumerNum + producerNum; i++) {
        if (threads[i].joinable())
            threads[i].join();
    }

    cout << "consumerNum: " << consumerNum << " producerNum: " << producerNum << endl;
    assert(sum == taskNum * producerNum);
}

void measureTime(Queue& q, int producer_num, int consumer_num, int task_num) {
    auto start = chrono::high_resolution_clock::now();
    startTask(q, producer_num, consumer_num, task_num);
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "time: " << (double)time.count() / 1000 << "\n\n";
}


int main() {
    vector<int> producer_nums = { 1, 2, 4 };
    vector<int> consumer_nums = { 1, 2, 4 };
    vector<size_t> queue_size = { 1, 4, 16 };
    int task_num = 4;

    for (auto producer_num : producer_nums)
    {
        for (auto consumer_num : consumer_nums)
        {
            DynamicMutexQueue q;
            measureTime(q, producer_num, consumer_num, task_num);


        }
    }

    return 0;
}