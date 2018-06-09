#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

unsigned int gArrMain[100000];

int GetMaxMed(int nArrSize, int nSubArrSize);

int compare_num(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

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
	//unsigned int* pSubArrTmp;

	int prevfirstDataTmp;
	int newDataTmp;

	//최초 한번은 부분배열을 구해서 퀵정렬을 수행한다.
	memcpy(pSubArrTmp, &gArrMain[0], nSubArrSize*sizeof(int));
	sort(pSubArrTmp, pSubArrTmp + nSubArrSize);

	nMedVal = pSubArrTmp[nMedIdx];
	if (nMaxMedVal < nMedVal)
		nMaxMedVal = nMedVal;


	int nKey;
	for (int i = 0; i < nSubArrCnt; i++)
	{
		//prevfirstDataTmp = pSubArrTmp[0];
		nKey = gArrMain[i];

		//이전 부분배열중 정렬되기 이전 상태의 맨 앞값을 찾아서 새로운 데이터로 교체한다.
		unsigned int* ptr = (unsigned int*)bsearch(&nKey, pSubArrTmp, nSubArrSize, sizeof(int), compare_num);
		unsigned keyIdx = ptr - pSubArrTmp;
		
		newDataTmp = gArrMain[i + nSubArrSize];		//새로운 부분배열의 마지막 데이터. 즉 새롭게 추가되는 하나의 데이터
		pSubArrTmp[keyIdx] = newDataTmp;

		sort(pSubArrTmp, pSubArrTmp + nSubArrSize);
		//nth_element(pSubArrTmp, pSubArrTmp + nMedIdx, pSubArrTmp + nSubArrSize);

		nMedVal = pSubArrTmp[nMedIdx];
		if (nMaxMedVal < nMedVal)
			nMaxMedVal = nMedVal;
	}

	delete[] pSubArrTmp;

	return nMaxMedVal;

}