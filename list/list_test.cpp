#include <iostream>

#include <list>

using namespace std;

int main()
{
	list<int> li;

	for (int i = 0; i < 5; i++)
		li.push_back(i * 2);

	list<int>::iterator it;
	for (it = li.begin(); it != li.end(); it++)
		printf("%d\n", *it);

	it = li.begin();
	it++;

	li.insert(it, 999);

	for (it = li.begin(); it != li.end(); it++)
		printf("%d\n", *it);



	

}