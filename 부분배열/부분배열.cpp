#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int gArrMain[100001];		//�ε��� 1���� ��뿹��
int gArrTmp[100001];		//�ε��� 1���� ��뿹��
int medPos;					//�߾���ġ�� ��Ÿ���� ����

int GetMaxMed(int nArrSize, int nSubArrSize);

inline void Swap(int& a, int& b)
{
	int tmp;
	tmp = a; a = b; b = tmp;
}

//select �Լ���
//partition �Լ��� �Բ� ����Ͽ��� �Ѵ�



//�� �Լ������� ���ذ��� �߽����� �������� ��������, ū���� ���������� �������̴�
int Partition(int start, int end)
{
	int left, right, size, key;

	key = gArrTmp[end];								//���Ƿ� �迭�� ������ �����͸� �������� ��Ҵ�
	
	for (left = start, right = end-1;; left++, right--)
	{
		//�迭 ������ ���غ��� ū ���� �ִ��� ã�´�
		while (gArrTmp[left] < key) left++;
		while (gArrTmp[right] > key) right--;
		if (right <= left)
			break;
		else
			Swap(gArrTmp[left], gArrTmp[right]);
	}

	Swap(gArrTmp[left], gArrTmp[end]);	//���ذ��� ��ȯ

	return left;
}

int select(int start, int end, int nth)
{
	if (start == end)
		return gArrTmp[start];

	int q = Partition(start, end);

	int kth = q - start + 1;

	if (nth<kth)
		return select(start, q-1, nth);			//���� �ٽ� ��Ƽ�Ŵ�
	else if (nth>kth)
		return select(q+1, end, nth - kth);		//������ �ٽ� ��Ƽ�Ŵ�
	else
	{
		return gArrTmp[q];					//�߾Ӱ� �߰�
	}
}

int main()
{
	int nTestCase;
	int nArrSize, nSubArrSize;

	freopen("test_input.txt", "r", stdin);

	cin >> nTestCase;
	for (int testnum = 0; testnum < nTestCase; testnum++)
	{
		memset(gArrMain, 0x00, sizeof(gArrMain));

		cin >> nArrSize >> nSubArrSize;

		for (int arridx = 1; arridx <= nArrSize; arridx++)
			cin >> gArrMain[arridx];


		//Ǯ��
		medPos = (nSubArrSize / 2)+1;
		int nSubArrCnt = nArrSize - nSubArrSize - 1;
		int ans;
		int max = 0;

		for (int i = 1; i <= nSubArrCnt; i++)
		{
			memset(gArrTmp, 0x00, sizeof(gArrTmp));
			memcpy(&gArrTmp[1], &gArrMain[i], sizeof(int)*nSubArrSize);
			ans = select(1, nSubArrSize, medPos);
			if (ans > max)
				max = ans;
		}

		printf("#%d %d\n", testnum + 1, max);
	}


	return 0;
}


int GetMaxMed(int nArrSize, int nSubArrSize)
{
	int nMedIdx = nSubArrSize/2;	//Median Index
	int nMedVal;
	int nMaxMedVal = 0;				//Max Median Value
	int nSubArrCnt = nArrSize - nSubArrSize - 1;

	unsigned int* pSubArrTmp = new unsigned int[nSubArrSize];
	//unsigned int* pSubArrTmp;

	for (int i = 0; i < nSubArrCnt; i++)
	{
		/*memcpy(pSubArrTmp, &gArrMain[i], nSubArrSize*sizeof(int));
		nth_element(pSubArrTmp, pSubArrTmp + nMedIdx, pSubArrTmp + nSubArrSize);
		
		nMedVal = pSubArrTmp[nMedIdx];
		if (nMaxMedVal < nMedVal)
		nMaxMedVal = nMedVal;*/
		

		nth_element(gArrMain+i, gArrMain+i + nMedIdx, gArrMain +i+ nSubArrSize);
		nMedVal = gArrMain[i+nMedIdx];
		if (nMaxMedVal < nMedVal)
			nMaxMedVal = nMedVal;


		
	}

	delete[] pSubArrTmp;

	return nMaxMedVal;

}