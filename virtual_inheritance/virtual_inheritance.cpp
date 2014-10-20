#include <iostream>

using namespace std;

class Animal {
public:
	virtual int getAge() const { return age; }
	virtual void eat() { cout << __FUNCTION__ << endl; }

private:
	int age;
};

// Two classes virtually inheriting Animal:
class Mammal : public virtual Animal {
public:
	virtual void breathe() { cout << __FUNCTION__ << endl; }
};

class WingedAnimal : public virtual Animal {
public:
	virtual void flap() { cout << __FUNCTION__ << endl; }
};

// A bat is still a winged mammal
class Bat : public Mammal, public WingedAnimal {
};

int main()
{
	Bat b;
	cout << b.getAge() << endl;

	return 0;
}