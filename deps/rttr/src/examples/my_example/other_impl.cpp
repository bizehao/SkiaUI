#include <rttr/registration>
#include <iostream>

using namespace rttr;

void add(int a)
{
	std::cout << a << std::endl;
}

RTTR_REGISTRATION
{
	registration::method("add", &add);
}