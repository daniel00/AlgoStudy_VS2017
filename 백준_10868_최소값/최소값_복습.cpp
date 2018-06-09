#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 100;

int src[100000 + 1];
int tree[4 * 100000 + 1];

int N, M;
int a, b;

int buildTree(int node, int start, int end)
{
	//리프노드일 경우
	if (start == end)
		return tree[node] = src[start];

	int mid = (start + end) / 2;
	return tree[node] = min(buildTree(node * 2, start, mid), buildTree(node * 2 + 1, mid + 1, end));
}

int getMin(int node, int start, int end, int qleft, int qright)
{
	if (qright < start || end < qleft)
		return INF;

	if (qleft <= start && end <= qright)
		return tree[node];

	int mid = (start + end) / 2;
	return min(getMin(node * 2, start, mid, qleft, qright), getMin(node * 2 + 1, mid + 1, end, qleft, qright));
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &src[i]);

	buildTree(1, 1, N);

	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", getMin(1, 1, N, a, b));
	}


	return 0;
}