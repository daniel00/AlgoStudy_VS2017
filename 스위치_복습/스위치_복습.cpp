#include <iostream>
#include <cstdio>

using namespace std;

int N, M;
int O, S, T;

const int MAXN = 100000;

int src[MAXN + 1];
int tree[4 * MAXN + 1];
int lazy[4 * MAXN + 1];

void updateLazy(int node, int start, int end)
{
	if (lazy[node] != 0) //1�̸� ������ �����϶�� �ǹ��̴�
	{
		//�����忡 lazy ����
		tree[node] = (end - start + 1) - tree[node];

		//������尡 �ƴϸ� �¿� ��忡 lazy����
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}

		//����� ������ ���ؼ� ����
		lazy[node] = 0;
	}
}

int updateRange(int node, int start, int end, int uleft, int uright)
{
	updateLazy(node, start, end);

	//������Ʈ ������ ���Ե��� ������ ���� ��尪 ����
	if (uright < start || end < uleft)
		return tree[node];
	
	//������Ʈ ������ ��尡 ������ ���Ե� ��쿡��, ��ǥ��忡 ���ؼ��� ������Ʈ�� �����ϰ� lazy�� �¿� ����Ʈ���� ǥ��
	if (uleft <= start && end <= uright)
	{
		tree[node] = (end - start + 1) - tree[node]; //��ǥ��忡 ���ؼ��� ������Ʈ(����) ����

		//��Ʈ��尡 �ƴҰ��, �¿�Ʈ���� lazy ����
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}
		return tree[node];
	}

	//�׿� ������Ʈ ������ ���� �Ϻθ� ��ġ�� ���, �¿켭��Ʈ�� ����
	tree[node] = updateRange(node*2, start, (start + end) / 2, uleft, uright) + updateRange(node*2+1, (start + end) / 2 + 1, end, uleft, uright);
	return tree[node];
}

int getSum(int node, int start, int end, int qleft, int qright)
{
	updateLazy(node, start, end);

	if (qright < start || end < qleft)
		return 0;

	if (qleft <= start && end <= qright)
		return tree[node];

	return getSum(node*2, start, (start + end) / 2, qleft, qright) + getSum(node*2+1, (start + end) / 2 + 1, end, qleft, qright);
}



int main()
{
	//updateRange(1, 1, 4, 1, 2);				// 1, 1, 0, 0
	//printf("%d\n", getSum(1, 1, 4, 1, 4));	// 2~3������ ����ġ ���������� 1

#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d %d", &O, &S, &T);
		if (O == 0)
			updateRange(1, 1, N, S, T);
		else if (O == 1)
			printf("%d\n", getSum(1, 1, N, S, T));
	}


	return 0;
}