#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 1e6;
ll src[MAXN + 1];
ll tree[4 * MAXN + 1];
ll lazy[4 * MAXN + 1];

int N, M, K;
int a, b, c, d;

ll buildTree(int node, int start, int end)
{
	if (start == end)
		return tree[node] = src[start];

	int mid = (start + end) / 2;
	return tree[node] = buildTree(node * 2, start, mid) + buildTree(node * 2 + 1, mid + 1, end);
}

void updateLazy(int node, int start, int end)
{
	//(1)�����忡 lazy�� �ݿ����ش�
	if (lazy[node] != 0)
	{
		tree[node] = (end - start + 1)*lazy[node];
	}

	//(2)������尡 �ƴϸ� �¿��忡 lazy�� �����Ѵ�
	if (start != end)
	{
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}

	//(3)�ߺ�ó�� ������ ���� lazy�� �����Ѵ�
	lazy[node] = 0;

}

void updateRange(int node, int start, int end, int uleft, int uright, int val)
{
	//lazy�� �ִ��� �����Ѵ�
	updateLazy(node, start, end);

	//��ġ�� ������ ������ ����
	if (uright < start || end < uleft)
		return;

	//��ǥ����̸� �����常 ������Ʈ�ϰ� , ������尡 �ƴҰ�� �¿��忡�� ǥ�ø� �صд�
	if (uleft <= start && end <= uright)
	{
		tree[node] += (end - start + 1)*val;
	
		if (start != end)
		{
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		
		return;
	}

	//��ǥ��尡 �ƴϸ� �¿��带 updateRange()�Ѵ�
	int mid = (start + end) / 2;
	updateRange(node * 2, start, mid, uleft, uright, val);
	updateRange(node * 2 + 1, mid + 1, end, uleft, uright, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll getSum(int node, int start, int end, int qleft, int qright)
{
	updateLazy(node, start, end);

	if (qright < start || end < qleft)
		return 0;

	if (qleft <= start && end <= qright)
		return tree[node];

	int mid = (start + end) / 2;
	return getSum(node * 2, start, mid, qleft, qright) + getSum(node * 2 + 1, mid + 1, end, qleft, qright);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d %d", &N, &M, &K);
	/*src.resize(N + 1);
	tree.resize(4 * N + 1);
	lazy.resize(4 * N + 1);*/
	for (int i = 1; i <= N; i++)
	{
		scanf("%lld", &src[i]);
	}

	buildTree(1, 1, N);

	for (int i = 1; i <= M + K; i++)
	{
		scanf("%d", &a);
		if (a == 1)
		{
			scanf("%d %d %lld", &b, &c, &d);
			updateRange(1, 1, N, b, c, d);
		}
		else if (a == 2)
		{
			scanf("%d %d", &b, &c);
			printf("%lld\n", getSum(1, 1, N, b, c));
		}
	}

	return 0;
}