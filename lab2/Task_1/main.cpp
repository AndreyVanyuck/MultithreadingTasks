#include "MutexArray.cpp"
#include "AtomicArray.cpp"
#include <vector>
#include <iostream>


void execute_task(BaseArray& a, int numThreads) {
    auto begin = chrono::steady_clock::now();

    vector<thread> threads;
    
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(thread([&]() { a.increment(); }));
    }

    for (int i = 0; i < numThreads; i++)
        if (threads[i].joinable()) {
            threads[i].join();
        }
    
    auto end = chrono::steady_clock::now();

    auto time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    
    cout << "Время работы при NumThreads = " << numThreads << ": "
        << (double)time.count() / 1000 << endl;
}

int main() {
   // setlocale(LC_ALL, "russian");
    
    MutexArray mutex_arr;
    AtomicArray atomic_arr;
    vector<int> NumThreads = { 4, 8, 16, 32 };

    cout << "C использованием mutex\n";

    for (auto num : NumThreads)
        execute_task(mutex_arr, num);

    cout << "\nC использованием atomic\n";

    for (auto num : NumThreads)
        execute_task(atomic_arr, num);

    return 0;
}

