#include "Nag³ówek.h"

#include <iostream>
#include <string>

int main()
{
	myVector <int> v;
	for (int i = 0; i < 20; i++)
		v.add(i);
	v.remove(17);
	v.remove(13);
	v.remove(12);
	v.remove(8);
	v.remove(4);
	v.remove(2);
	v.remove(1);
	v.add(50);
	v.add(51);
	v.add(52);
	v.add(53);
	for (int i = 0; i < 17; i++)
		std::cout << v.get(i) << std::endl;
	myVector <std::string> v2(1);
	v2.add("test");
	std::cout << v2.last() << std::endl;

	float test1 = 20.5;
	int test2 = 10;
	function(test1, test2);
	std::cout << test1 << std::endl;
	function(test1);
	std::cout << test1 << std::endl;
}