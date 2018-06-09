

#include <cstdio>
#include <iostream>
#include <algorithm>

//#define _CRT_SECURE_NO_WARNNINGS
#pragma warning(disable:4996)

using namespace std;

const int MAXN = 100000;
long long src[MAXN + 1];
long long D[MAXN + 1];
int N;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &src[i]);

	D[0] = 0;
	long long maxSum = -1000;
	for (int i = 1; i <= N; i++)
	{
		D[i] = max(D[i - 1] + src[i], src[i]);	//이전까지 더한값과 , 현재값중 큰 값을 취한다
		if (D[i] > maxSum)
			maxSum = D[i];
	}

	printf("%lld", maxSum);
	return 0;
}