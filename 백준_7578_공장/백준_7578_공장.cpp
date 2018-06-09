#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;

int A[MAXN + 1];
int B[MAXN + 1];
int BIT[MAXN + 1];

int N;

void updateBIT(int idx, int val)
{
	while (idx <= N)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

int getSum(int idx)
{
	int ans = 0;
	while (idx >= 1)
	{
		ans += BIT[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif
	scanf("%d", &N);

	int valTmp;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &valTmp);
		A[valTmp] = i;			//val-->index로 변환
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &valTmp);
		B[i] = A[valTmp];			//val-->index로 변환
	}

	long long invCnt = 0;
	for (int i = N; i >= 1; i--)
	{
		invCnt += getSum(B[i] - 1);
		updateBIT(B[i], 1);
	}

	printf("%lld\n", invCnt);

	return 0;
}