#ifndef _FACADE_H_
#define _FACADE_H_

#include <iostream>
#include <memory>

class Subsystem1 {
public:
	void Operation() { std::cout << "Subsytem 1" << std::endl; }
};

class Subsystem2 {
public:
	void Operation() { std::cout << "Subsytem 2" << std::endl; }
};

class Facade {
public:
	Facade() {
		_system1 = std::make_shared<Subsystem1>();
		_system2 = std::make_shared<Subsystem2>();
	}

	void OperationWrapper() {
		_system1->Operation();
		_system2->Operation();
	}

private:
	std::shared_ptr<Subsystem1> _system1;
	std::shared_ptr<Subsystem2> _system2;
};

#endif // _FACADE_H_