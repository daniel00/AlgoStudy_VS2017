#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

typedef long long ll;

const int INF = 1e9 + 100;
const int MAXN = 500000;

int srcVal[MAXN + 1];		//값이 저장되어있는 배열
							//int srcCpy[MAXN+1];		//복사
							//int BIT[MAXN+1];		//숫자의 출현빈도가 저장된 Binary Indexed Tree
vector<int> BIT;
int N;

void updateBIT(int idx, int val)
{
	while (idx <= N)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

ll getAccSum(int idx)
{
	ll ans = 0;
	while (idx >= 1)
	{
		ans += BIT[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

void CovertValToIndex()
{
	int* srcCpy = new int[N + 1];

	for (int i = 1; i <= N; i++)
		srcCpy[i] = srcVal[i];

	sort(srcCpy + 1, srcCpy + N + 1);

	for (int i = 1; i <= N; i++)
	{
		srcVal[i] = lower_bound(srcCpy + 1, srcCpy + 1 + N, srcVal[i]) - srcCpy;
		//srcCpy[srcVal[i]] = INF;
	}

	delete[] srcCpy;
}

ll getInvCnt()
{
	ll ans = 0;
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
	freopen("sample_input.txt", "r", stdin);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &srcVal[i]);
	}

	CovertValToIndex();
	BIT.resize(N + 1);

	printf("%d", getInvCnt());

	return 0;
}