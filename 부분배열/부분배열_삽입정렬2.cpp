#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

unsigned int gArrMain[100000];

int GetMaxMed(int nArrSize, int nSubArrSize);

int main()
{
	int nTestCase;
	int nArrSize, nSubArrSize;

	freopen("test_input.txt", "r", stdin);

	cin >> nTestCase;
	for (int testnum = 0; testnum < nTestCase; testnum++)
	{
		cin >> nArrSize >> nSubArrSize;

		for (int arridx = 0; arridx < nArrSize; arridx++)
			cin >> gArrMain[arridx];

		printf("%d %d\n", testnum + 1, GetMaxMed(nArrSize, nSubArrSize));
	}


	return 0;
}


int GetMaxMed(int nArrSize, int nSubArrSize)
{
	int nMedIdx = nSubArrSize / 2;	//Median Index
	int nMedVal;
	int nMaxMedVal = 0;				//Max Median Value
	int nSubArrCnt = nArrSize - nSubArrSize - 1;

	unsigned int* pSubArrTmp = new unsigned int[nSubArrSize];

	//원본배열중 부분배열 크기만큼만 복사한다. 함수내로 넘길값이다.
	memcpy(pSubArrTmp, &gArrMain[0], nSubArrSize * sizeof(int));
	sort()

	for (int i = 0; i < nSubArrCnt; i++)
	{
		

		//원본배열을 정해진 영역만큼 정렬한다.
		InsertSort(pSubArrTmp, nSubArrSize);

		//중앙값을 구한다
		nMedVal = pSubArrTmp[nMedIdx];

		//최대중앙값인지 판별한다
		if (nMaxMedVal < nMedVal)
			nMaxMedVal = nMedVal;

	}

	for (int i = 0; i < nSubArrCnt; i++)
	{

	}

	delete[] pSubArrTmp;

	return nMaxMedVal;

}