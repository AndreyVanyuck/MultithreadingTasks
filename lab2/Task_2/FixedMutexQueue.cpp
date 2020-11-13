#include "Queue.cpp"

class FixedMutexQueue : public Queue
{
private: 	
	queue<uint8_t> queue;
	size_t size_;
	mutex mutex;
	condition_variable push_condition_variable;
	condition_variable pop_condition_variable;

public:
	FixedMutexQueue(size_t size) : size_(size) {}

	void push(uint8_t val) override
	{
		unique_lock<std::mutex> unq_lock(mutex);
		push_condition_variable.wait(unq_lock, [&] { return queue.size() < size_; });
		queue.push(val);
		pop_condition_variable.notify_one();
	}

	bool pop(uint8_t& val) override
	{
		unique_lock<std::mutex> unq_lock(mutex);
		if (pop_condition_variable.wait_for(unq_lock, std::chrono::milliseconds(1), [&] { return !queue.empty(); }))
		{
			val = queue.front();
			queue.pop();
			push_condition_variable.notify_one();
			return true;
		}
		else
			return false;
	}
	string to_string() override
	{
		return "FixedMutexQueue ";
	}
};