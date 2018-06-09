#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int gArrMain[100001];		//인덱스 1부터 사용예정
int gArrTmp[100001];		//인덱스 1부터 사용예정
int medPos;					//중앙위치를 나타내는 변수

int GetMaxMed(int nArrSize, int nSubArrSize);

inline void Swap(int& a, int& b)
{
	int tmp;
	tmp = a; a = b; b = tmp;
}

//select 함수와
//partition 함수를 함께 사용하여야 한다



//이 함수에서는 기준값을 중심으로 작은값은 왼쪽으로, 큰값은 오른쪽으로 보낼것이다
int Partition(int start, int end)
{
	int left, right, size, key;

	key = gArrTmp[end];								//임의로 배열의 마지막 데이터를 기준으로 잡았다
	
	for (left = start, right = end-1;; left++, right--)
	{
		//배열 좌측에 기준보다 큰 수가 있는지 찾는다
		while (gArrTmp[left] < key) left++;
		while (gArrTmp[right] > key) right--;
		if (right <= left)
			break;
		else
			Swap(gArrTmp[left], gArrTmp[right]);
	}

	Swap(gArrTmp[left], gArrTmp[end]);	//기준값과 교환

	return left;
}

int select(int start, int end, int nth)
{
	if (start == end)
		return gArrTmp[start];

	int q = Partition(start, end);

	int kth = q - start + 1;

	if (nth<kth)
		return select(start, q-1, nth);			//왼쪽 다시 파티셔닝
	else if (nth>kth)
		return select(q+1, end, nth - kth);		//오른쪽 다시 파티셔닝
	else
	{
		return gArrTmp[q];					//중앙값 발견
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


		//풀이
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