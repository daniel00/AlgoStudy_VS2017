/*
����
� N���� ���� �־��� �ִ�. �׷��� �߰��� ���� ������ ����� �Ͼ�� �� �߰��� � �κ��� ���� ���Ϸ� �Ѵ�. 
���࿡ 1,2,3,4,5 ��� ���� �ְ�, 3��°���� 4��° ���� 6�� ���ϸ� 1, 2, 9, 10, 5�� �ǰ�, ���⼭ 2��°���� 5��°���� ���� ���϶�� �Ѵٸ� 26�� ����ϸ� �Ǵ� ���̴�. 
�׸��� �� ���¿��� 1��°���� 3��° ���� 2�� ���� 2��°���� 5��°���� ���� ���϶�� �Ѵٸ� 22�� �� ���̴�.

�Է�
ù° �ٿ� ���� ���� N(1<=N<=1,000,000)�� M(1<=M<=10,000), K(1<=k<=10,000) �� �־�����. 
M�� ���� ������ �Ͼ�� ȸ���̰�, K�� ������ ���� ���ϴ� ȸ���̴�. 
�׸��� ��° �ٺ��� N+1��° �ٱ��� N���� ���� �־�����. 
�׸��� N+2��° �ٺ��� N+M+K+1��° �ٱ��� �� ���� ���� a,b,c �Ǵ� a,b,c,d�� �־����µ�, 
a�� 1�� ��� b��° ������ c��° ���� d�� ���ϰ�, a�� 2�� ��쿡�� b���� c������ ���� ���Ͽ� ����ϸ� �ȴ�.

���
ù° �ٺ��� K�ٿ� ���� ���� ������ ���� ����Ѵ�. (�� ������ long long ������ ���� �ʴ´�)
*/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6;
vector<ll> src;
vector<ll> tree;	//�뷫4���ϸ� Ʈ��������� �����
vector<ll> lazy;

int N, M, K;
ll a, b, c, d;

ll buildTree(int node, int start, int end)
{
	//leaf node
	if (start == end)
		return tree[node] = src[start];

	return tree[node] = buildTree(node * 2, start, (start + end) / 2) + buildTree(node * 2 + 1, (start + end) / 2 + 1, end);
}

void checkLazy(int node, int start, int end)
{
	if (lazy[node] != 0)
	{
		//(1)�����忡 Lazy�� �ݿ����ش�(�̹� ���������� ���ϱ�)
		tree[node] += (end - start + 1)*lazy[node];

		//(2)������尡 �ƴҰ��, ���� Ʈ���� lazy�� ������ �ش�
		if (start != end)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		//(3)���� ����� Lazy�� 0���� �����Ѵ�
		lazy[node] = 0;
	}
}

//qleft : query left, qright : query right
ll getSum(int node, int start, int end, int qleft, int qright)
{
	checkLazy(node, start, end);

	if (qright < start || end < qleft)
		return 0;

	if (qleft <= start && end <= qright) //��������� �� ���� �ʿ䰡 ����
		return tree[node];

	return getSum(node * 2, start , (start + end) / 2, qleft, qright) + getSum(node * 2 + 1, (start + end) / 2 + 1, end, qleft, qright);
}



//uleft, uright : update left, right
void updateRange(int node, int start, int end, int uleft, int uright, ll diff)
{
	//lazy�� �ִ��� ����
	checkLazy(node, start, end);

	//���� ��尡 ������Ʈ ������ ��ġ�� ������ �׳� ����
	if (uright < start || end < uleft)
		return;

	/*************************************************************************************/
	//Lazy Propagation�� �ٽ�
	//��ǥ������� ���ؼ��� ������Ʈ�� �����ϰ�, ����Ʈ������ ǥ�ø� ���ش�!!!!!!
	//��ǥ������� : ������Ʈ ������ ������ ���ԵǴ� ���
	if (uleft <= start && end <= uright)
	{
		//��ǥ���� ������Ʈ
		tree[node] += (end - start + 1)*diff;		

		//������尡 �ƴϸ�, �¿� ����Ʈ���� Lazyǥ��
		if (start != end)
		{
			lazy[node * 2] += diff;
			lazy[node * 2+1] += diff;
		}
		return;
	}
	/*************************************************************************************/


	//��ǥ������ �ƴϿ��� ��� �¿�����Ʈ�� ������Ʈ
	updateRange(node*2, start, (start + end) / 2, uleft, uright, diff);
	updateRange(node*2+1, (start + end) / 2 + 1, end, uleft, uright, diff);

	//���� ����Ʈ�� ������Ʈ�� ������ �����ϸ� ���� ����� ���� �¿����� ����� ������ ������Ʈ
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}


int main()
{
	/* test
	src = { 0,1,2,3,4,5 };
	tree.resize(4 * 6 + 1);
	lazy.resize(4 * 6 + 1);

	buildTree(1, 1, 5);
	updateRange(1, 1, 5, 1, 3, 1);					//{0,2,3,4,4,5}

	printf("sum : %d\n", getSum(1, 1, 5, 1, 3));	//answer : 9
	*/
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d %d", &N, &M, &K);
	src.resize(N + 1);
	tree.resize(4 * N + 1);
	lazy.resize(4 * N + 1);
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