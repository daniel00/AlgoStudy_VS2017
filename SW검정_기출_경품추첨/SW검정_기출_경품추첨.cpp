#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

const int MAXN = 100000;
int BIT[MAXN + 1];

void update(int idx, int val)
{
	while (idx <= MAXN)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

int getSum(int idx)
{
	int sum = 0;
	while (idx>=1)
	{
		sum += BIT[idx];
		idx -= (idx&-idx);
	}
	return sum;
}

int findkthNum(int k)
{
	int start = 1;
	int end = MAXN;
	int mid;

	while (start < end)
	{
		mid = (start + end) / 2;
		if (getSum(mid) >= k)
			end = mid;
		else
			start = mid + 1;
	}
	return end;
}


int main()
{
	int T, Q, act, num;
	
	freopen("sample_input_small.txt", "r", stdin);
	FILE* f = fopen("sample_output_small.txt", "w");

	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		printf("#%d ", t + 1); fprintf(f, "#%d ", t + 1);
		scanf("%d", &Q);
		while (Q--)
		{
			scanf("%d %d", &act, &num);

			if (act == 1)
				update(num, 1);
			else if (act == 2)
			{
				int kthNum = findkthNum(num);
				printf("%d ", kthNum);	fprintf(f, "%d ", kthNum);
				update(kthNum, -1);
			}
		}
		printf("\n"); fprintf(f, "\n");
	}
	//************************************************************
	//test
	/*int arr[] = { 0, 1,2,2,3,3,3,4,4,4 };
	int arrsize = sizeof(arr) / sizeof(int);
	for (int i = 1; i <= arrsize-1; i++)
	{
		update(arr[i], 1);
	}
	int kthNum;
	kthNum = findkthNum(2);
	kthNum = findkthNum(4);
	kthNum = findkthNum(6);*/
	//************************************************************

	return 0;
}