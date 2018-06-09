#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

const int maxnum = 10000;


//typedef pair<int, int> pii;
//pii arr[maxnum];

int main()
{
	int arrNum[] = { 3, 7, 23, 10, 4, 27, 89, 100 };
	int sizearr = sizeof(arrNum) / sizeof(int);

	sort(arrNum, arrNum + sizearr);						//작은수 부터 큰수로
	//sort(arrNum, arrNum + sizearr, greater<int>());	//큰수	부터 작은수로


	for (int i = 0; i < sizearr; i++)
	{
		cout << arrNum[i] << " ";
	}

	cout << "\n";

	//system("pause");
}