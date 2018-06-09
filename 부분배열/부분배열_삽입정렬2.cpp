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

	//�����迭�� �κй迭 ũ�⸸ŭ�� �����Ѵ�. �Լ����� �ѱ氪�̴�.
	memcpy(pSubArrTmp, &gArrMain[0], nSubArrSize * sizeof(int));
	sort()

	for (int i = 0; i < nSubArrCnt; i++)
	{
		

		//�����迭�� ������ ������ŭ �����Ѵ�.
		InsertSort(pSubArrTmp, nSubArrSize);

		//�߾Ӱ��� ���Ѵ�
		nMedVal = pSubArrTmp[nMedIdx];

		//�ִ��߾Ӱ����� �Ǻ��Ѵ�
		if (nMaxMedVal < nMedVal)
			nMaxMedVal = nMedVal;

	}

	for (int i = 0; i < nSubArrCnt; i++)
	{

	}

	delete[] pSubArrTmp;

	return nMaxMedVal;

}