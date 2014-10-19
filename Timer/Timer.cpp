#include <iostream>
#include <chrono>
#include <ratio>

using namespace std;

void test2() {
	auto tp = chrono::steady_clock::now();
	auto d1 = chrono::time_point_cast<chrono::hours>(tp);
	cout << "hours since start of epoch: " << d1.time_since_epoch().count() << endl;

	using days = chrono::duration<long, ratio<24 * 60 * 60, 1>>; // a day's duration
	auto d2 = chrono::time_point_cast<days>(tp);
	cout << "days since start of epoch: " << d2.time_since_epoch().count() << endl;
}

void main()
{
	chrono::steady_clock::time_point t = chrono::steady_clock::now();
	for (size_t i = 0; i < 1000000; i++) { }
	chrono::steady_clock::duration d = chrono::steady_clock::now() - t;
	cout << "use time: " << d.count() << endl;
	cout << "use time: " << chrono::duration_cast<chrono::microseconds>(d).count() << endl;
	cout << "use time: " << chrono::duration_cast<chrono::milliseconds>(d).count() << endl;

	test2();
}