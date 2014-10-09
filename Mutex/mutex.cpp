#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex count_mutex;	// represent the right to use cout


template<typename Arg1>
void write_out(Arg1 a1) {
	thread::id name = this_thread::get_id();
	count_mutex.lock();
	cout << "From thread " << name << ": " << a1 << endl;
	count_mutex.unlock();
}

void hello() {
	count_mutex.lock();
	cout << "Hello, ";
	count_mutex.unlock();
}

void world() {
	count_mutex.lock();
	cout << "World!";
	count_mutex.unlock();
}

mutex foo, bar;

void task_a() {
	cout << __LINE__ << endl;
	std::lock(foo, bar);	// simultaneous lock (prevents deadlock)
	cout << __LINE__ << endl;
	unique_lock<mutex> lck1(foo, std::adopt_lock);
	unique_lock<mutex> lck2(bar, std::adopt_lock);

	cout << "task a running ..." << endl;
}

void task_b() {
	unique_lock<mutex> lck1, lck2;
	lck1 = unique_lock<mutex>(bar, std::defer_lock);
	lck2 = unique_lock<mutex>(foo, std::defer_lock);

	std::lock(lck1, lck2);

	cout << "task b running ..." << endl;
}


void main()
{
	unique_lock<mutex> lc1(bar);
	thread t1(task_a);
	thread t2(task_b);

	t1.join();
	t2.join();
}