#include <iostream>

#include <vector>

using namespace std;

int main()
{
	vector<int> v;

	v.push_back(5);
	v.push_back(4);
	v.push_back(3);
	

	printf("%d\n", v.front());
	printf("%d\n", v.back());
	printf("v.at(2) : %d\n", v.at(2));

	return 0;
}