/**************************************************************
Problem: 2736
User: daniel00
Language: C++
Result: Accepted
****************************************************************/


//정올 2736과 같은문제 http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1999&sca=50

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>

using namespace std;

const int INF = 1e9 + 100;
const int MAXN = 500000;

int srcVal[MAXN + 1];     //값이 저장되어있는 배열
int srcCpy[MAXN + 1];     //복사
						  //int srcIdx[MAXN+1];       //인덱스가 저장되도록 변경한 배열

int BIT[MAXN + 1];        //숫자의 출현빈도가 저장된 Binary Indexed Tree

int N;

void Swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void updateBIT(int idx, int val)
{
	while (idx <= N)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

int getAccSum(int idx)
{
	int ans = 0;
	while (idx >= 1)
	{
		ans += BIT[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

void CovertValToIndex()
{
	for (int i = 1; i <= N; i++)
		srcCpy[i] = srcVal[i];

	sort(srcCpy + 1, srcCpy + N + 1);

	for (int i = 1; i <= N; i++)
	{
		//BIT를 위해 1베이스로 저장하여야 하는데 우리는 루프를 1부터 도니깐 별도로 처리할 필요는 없다.
		srcVal[i] = lower_bound(srcCpy + 1, srcCpy + 1 + N, srcVal[i]) - srcCpy;
	}
}

int getInvCnt()
{
	int ans = 0;

	int minCnt = INF;
	int maxCnt = 0;
	int minVal = INF;
	int maxVal = 0;
	int minCntIdx = INF;
	int maxCntIdx = INF;

	for (int i = N; i >= 1; i--)
	{
		int Cnt = getAccSum(srcVal[i] - 1);
		if (Cnt <= minCnt)
		{
			minCnt = Cnt;
			if (srcVal[i] <= minVal)
			{
				minVal = srcVal[i];
				minCntIdx = i;
			}
		}
		if (Cnt >= maxCnt)
		{
			maxCnt = Cnt;
			if (srcVal[i] >= maxVal)
			{
				maxVal = srcVal[i];
				maxCntIdx = i;
			}
		}
		updateBIT(srcVal[i], 1);
	}
	/*if (minCntIdx == maxCntIdx)
	{
		if (srcVal[minCntIdx]<srcVal[maxCntIdx])
			maxCntIdx = maxCntIdx + 1;
		else
			minCntIdx = minCntIdx + 1;
	}*/

	Swap(srcVal[minCntIdx], srcVal[maxCntIdx]);

	memset(BIT, 0, sizeof(int)*(N + 1));
	for (int i = N; i >= 1; i--)
	{
		ans += getAccSum(srcVal[i] - 1);
		updateBIT(srcVal[i], 1);
	}

	return ans;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input2.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &srcVal[i]);
	}

	CovertValToIndex();

	//printf("%d", getInvCnt());

	int minCount = getInvCnt();
	printf("%d\n", minCount);

	return 0;
}