#include <cstdio>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex g_lock;

void func()
{
	//g_lock.lock();

	std::unique_lock<std::mutex> unique_lock(g_lock);

	printf("entered thread id: %d\n", std::this_thread::get_id());
	std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
	printf("leaving thread id: %d\n", std::this_thread::get_id());

	//g_lock.unlock();
}

void main()
{
	srand((unsigned int)time(nullptr));

	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();
}