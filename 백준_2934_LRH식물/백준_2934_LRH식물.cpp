#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 100000;
int BIT[MAXN + 1];

int N;

void update(int idx, int val)
{
	while (idx <= MAXN+1)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

void updateRange(int a, int b, int val)
{
	update(a, val);
	update(b + 1, -val);
}

int getPointSum(int idx)
{
	int sum = 0;
	while (idx >= 1)
	{
		sum += BIT[idx];
		idx -= (idx&-idx);
	}
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE
	scanf("%d", &N);
	
	int l, r;
	int lsum, rsum;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &l, &r);

		//get sum of flowers
		lsum = getPointSum(l);
		rsum = getPointSum(r);
		printf("%d\n", lsum + rsum);

		//reset left,right to zero
		updateRange(l, l, -lsum);
		updateRange(r, r, -rsum);

		//add range by one
		updateRange(l + 1, r - 1, 1);
	}

	return 0;
}
