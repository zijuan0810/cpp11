#include <vector>
#include <cstdio>
#include <mutex>
#include <cstdarg>
#include <iostream>
#include <thread>
#include <chrono>

/*
 * 在这个例子中，通常我们会使用
 */

template <typename T>
class vector_thread
{
public:
	void push_back(T e)
	{
		std::unique_lock<std::recursive_mutex> unique_lock(_lock);
		_vector.push_back(e);
	}

	void push_back_range(int num, ...)
	{
		va_list args;
		va_start(args, num);
		for (int i = 0; i < num; i++) {
			std::unique_lock<std::recursive_mutex> unique_lock(_lock);
			this->push_back(va_arg(args, T));
		}
		va_end(args);
	}

	/// 垃圾处理
	void dump()
	{
		std::unique_lock<std::recursive_mutex> unique_lock(_lock);
		for (auto& e : _vector) {
			std::cout << e << std::endl;
		}
	}

private:
	//std::mutex _lock;
	std::recursive_mutex _lock;
	std::vector<T> _vector;
};

void func(unsigned int nRand, vector_thread<int>& vec)
{
	srand(nRand);
	vec.push_back_range(3, rand(), rand(), rand());
}


void main()
{
	unsigned int rand1 = (unsigned int)time(nullptr) + 1;
	unsigned int rand2 = (unsigned int)time(nullptr) + 2;
	unsigned int rand3 = (unsigned int)time(nullptr) + 3;

	vector_thread<int> vec;
	std::thread t1(func, rand1, std::ref(vec));
	std::thread t2(func, rand2, std::ref(vec));
	std::thread t3(func, rand3, std::ref(vec));

	t1.join();
	t2.join();
	t3.join();

	vec.dump();
}