#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

const int MAXN = 1000;

int C;
int N;
int L;

int SRC[MAXN+1];
int BIT[MAXN + 1];

void update(int idx, int val)
{
	while (idx <= MAXN)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

double getAccSum(int idx)
{
	double sum = 0;
	while (idx >=1)
	{
		sum += BIT[idx];
		idx -= (idx&-idx);
	}
	return sum;
}

double getRangeSum(int a, int b)
{
	return getAccSum(b) - getAccSum(a - 1);
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &C);
	for (int c = 0; c < C; c++)
	{
		memset(SRC, 0, sizeof(SRC));
		memset(BIT, 0, sizeof(BIT));

		scanf("%d %d", &N, &L);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &SRC[i]);
			update(i, SRC[i]);
		}

		double min = 9999999999;
		double ans;

		for (int k = L; k <= N; k++)
		{
			for (int i = 1; i <= N-k+1; i++)
			{
				ans = double(getRangeSum(i, i + k-1)/k);
				if (ans < min)
					min = ans;
			}
		}
		printf("%.10f\n", min);
	}
	return 0;
}