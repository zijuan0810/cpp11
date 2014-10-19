#include "Facade.h"
#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstdio>

using namespace std;

void main()
{
	shared_ptr<Facade> facade = make_shared<Facade>();
	facade->OperationWrapper();
}