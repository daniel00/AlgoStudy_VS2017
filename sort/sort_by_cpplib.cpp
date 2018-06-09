#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
	int arrNum[] = { 3, 7, 23, 10, 4, 27, 89, 100 };
	int sizearr = sizeof(arrNum) / sizeof(int);

	sort(arrNum, arrNum + sizearr, greater<int>());


	for (int i = 0; i < sizearr; i++)
	{
		cout << arrNum[i] <<" ";
	}

	cout << "\n";

	system("pause");
}