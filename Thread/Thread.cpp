#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void print_id(const thread& td) {
	if (td.get_id() == thread::id{}) {
		cout << "td not joinable" << endl;
	}
	else {
		cout << "td's id is " << td.get_id() << endl;
	}
}

void tick(int n) {
	for (int i = 0; i != n; ++i) {
		this_thread::sleep_for(chrono::seconds{ 1 });
		//cout << chrono::system_clock::now() << "Alive!" << endl;
	}
}

void main()
{
	auto t1 = chrono::system_clock::now();

	thread timer{ tick, 10 };
	timer.join();

	auto t2 = chrono::system_clock::now();
	int elapsed_seconds = (chrono::duration_cast<chrono::milliseconds>(t2 - t1)).count();
	cout << "elapsed seconds: " << elapsed_seconds << endl;
}