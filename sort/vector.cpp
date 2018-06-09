#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int main()
{
	vector<int> num_vector { 5, 4, 2, 10 };

	for (auto num : num_vector)
	{
		printf("%d ",num);
	}
	printf("\n");
	system("pause");

}