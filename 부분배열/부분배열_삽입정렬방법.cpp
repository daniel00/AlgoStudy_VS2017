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

	//���� �ѹ��� �κй迭�� ���ؼ� �������� �����Ѵ�.
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

		//���� �κй迭�� ���ĵǱ� ���� ������ �� �հ��� ã�Ƽ� ���ο� �����ͷ� ��ü�Ѵ�.
		unsigned int* ptr = (unsigned int*)bsearch(&nKey, pSubArrTmp, nSubArrSize, sizeof(int), compare_num);
		unsigned keyIdx = ptr - pSubArrTmp;
		
		newDataTmp = gArrMain[i + nSubArrSize];		//���ο� �κй迭�� ������ ������. �� ���Ӱ� �߰��Ǵ� �ϳ��� ������
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