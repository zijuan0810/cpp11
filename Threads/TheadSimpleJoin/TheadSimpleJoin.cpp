#include <cstdio>
#include <iostream>
#include <thread>
#include <exception>
#include <mutex>
#include <vector>

std::mutex g_mutex;
std::vector<std::exception_ptr> g_exceptions;

void throw_function()
{
	throw std::exception("somthing wrong happend");
}

void func()
{
	try {
		throw_function();
	}
	catch (...) {
		std::lock_guard<std::mutex> lock(g_mutex); // ��֤ͬһʱ��ֻ��һ���߳̿���push����
		g_exceptions.push_back(std::current_exception());
	}
}

void main()
{
	g_exceptions.clear();

	std::thread t(func);
	t.join();

	for ( auto& e : g_exceptions ) {
		try {
			if (e != nullptr) {
				std::rethrow_exception(e);
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}