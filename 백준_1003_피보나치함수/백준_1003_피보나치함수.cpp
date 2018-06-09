#include <iostream>
#include <cstdio>

using namespace std;

int T;
int N;
int cnt0, cnt1;

int d[41];

int fibonacci(int n) 
{
	
	if (n == 0) 
	{
		//printf("0");
		cnt0++;
		return 0;
	}
	else if (n == 1) 
	{
		//printf("1");
		cnt1++;
		return 1;
	}
	else 
	{
		int a = n - 1;
		int b = n - 2;
		return fibonacci(a) + fibonacci(b);
	}
}

void fib(int n)
{
	for (int i = 0; i <= n; i++)
	{
		if (i == 0)
			d[i] = 0;
		else if (i == 1)
			d[i] = 1;
		else if (i == 2)
			d[i] = 1;
		else
			d[i] = d[i - 1] + d[i - 2];
	}
	
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);

#endif // !ONLINE_JUDGE
	scanf("%d", &T);
	fib(40);	//일단 한번 구해놓는다
	for (int t = 0; t < T; t++)
	{
		scanf("%d", &N);
		//(1)솔루션1
		//cnt0 = cnt1 = 0;
		//fibonacci(N);
		//printf("%d %d\n", cnt0, cnt1);

		//(2)솔루션2
		if (N == 0)
			printf("1 0\n");
		else if (N == 1)
			printf("0 1\n");
		else
			printf("%d %d\n", d[N - 1], d[N]);
	}

	return 0;
}