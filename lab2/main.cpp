#include "MutexArray.cpp"
//#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
//#include <queue>


void execute(BaseArray& a, int numThreads) {
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(std::thread([&]() { a.increment(); }));
       // threads[i].join();
    }
    for (int i = 0; i < numThreads; i++)
        threads[i].join();
}

void measureTime(BaseArray& a, int numThreads) {
    auto begin = std::chrono::steady_clock::now();
    execute(a, numThreads);
    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Running time at NumThreads = " << numThreads << ": "
        << (double)time.count() / 1000 << std::endl;
}

int main() {
    MutexArray mutex_arr;
    std::vector<int> NumThreads = { 4, 8, 16, 32 };

    for (auto num : NumThreads)
        measureTime(mutex_arr, num);

    std::cout << std::endl;

    return 0;
}

