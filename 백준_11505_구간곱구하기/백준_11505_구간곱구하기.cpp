#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAXN = (int)1e6;
const int MOD = (int)1e9 + 7;	//1,000,000,007
//ll src[MAXN+1];
//ll tree[MAXN*4 + 1];

vector<ll> src(0);
vector<ll> tree(0);

int N, M, K;
int a, b;
ll c;

ll buildTree(int node, int start, int end)
{
	if (start == end)
		return tree[node] = src[start];
	else
	{
		return tree[node] = ((buildTree(node * 2, start, (start + end) / 2)) * (buildTree(node * 2 + 1, (start + end) / 2 + 1, end))) % MOD; 
	}

	return 0;
}


//������ ���׸�ƮƮ���� ������Ʈ�� ��� ������ó�� diff���� ���Ҽ��� ����.
//������� � ��������� ���� 4���� 6���� �����ϴ� ��츦 �����غ���.
//�����տ����� ���������� ������ diff==2�� ���õ� ��忡 ��� ���ϸ� �Ǿ����� �������� �׷����� ����.
//��ȭ���� 6/4�� �� ��忡 �� �����ٰ��ΰ�? �̰� �������� �����ϴ�. �� �м������� �Ͽ��� ��쿡�� �����ϰ� �Ҽ������� �ϰԵǸ� ������ �߻��ϰ� �ȴ�.
//������ ��ǻ�ʹ� ������ ���꿡�� ������ �����ϰ� �ǹǷ� ��Ȯ�� ���� ���� �� ����.
//�׷��� ��� �� ���ΰ�? �׷� �׳� ����ϰ� �������� �ٲپ��ְ� ���Ӱ� �����ϴ°� �� ���ϰڴ�.
//�׷��� �Ʒ��� ���� ��ġ buildTree()�� ������ ������ update()�Լ��� ����ϰ� �ȴ�.
ll updateTree(int node, int start, int end, int index, ll val)
{
	if (index<start || end<index)
		return tree[node];	//������ ��ȯ

	if (start == end)
		return tree[node] = val;
	
	return tree[node] = (updateTree(node * 2, start, (start + end) / 2, index, val) * updateTree(node * 2 + 1, (start + end) / 2 + 1, end, index, val)) % MOD;
}

//void updateTree(int node, int start, int end, int index, float rate)
//{
//	if (index < start || end < index)
//		return;
//
//	tree[node] *= rate;
//	if (start != end)
//	{
//		updateTree(node*2, start, (start + end) / 2, index, rate);
//		updateTree(node*2+1, (start + end) / 2 + 1, end, index, rate);
//	}
//}

ll getMul(int node , int start, int end, int left, int right)
{
	
	if (left > end || right < start)
		return 1;		//�̺κ��� �� ���Ҷ� �߿��ϴ�!!!!!!!
	
	if (left <= start && right >= end)
		return tree[node];

	return (getMul(node * 2, start, (start + end) / 2, left, right) * getMul(node * 2 + 1, (start + end) / 2 + 1, end, left, right))%MOD;
}

int main()
{
	//test
	/*src = { 0,1,2,3,4,5 };
	tree.resize(5 * 4 + 1);
	buildTree(1, 1, 5);
	printf("%lld\n", getMul(1, 1, 5, 2, 3));*/

	freopen("sample_input2.txt", "r", stdin);

	scanf("%d %d %d", &N, &M, &K);
	
	src.resize(N + 1);
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	tree.resize(tree_size + 1);


	for (int i = 1; i <= N; i++)
	{
		scanf("%lld", &src[i]);
	}
	buildTree(1, 1, N);

	for (int i = 1; i <= M+K; i++)
	{
		scanf("%d %d %lld", &a, &b, &c);
		if (a == 1)
		{
			//src[b] = c;
			updateTree(1, 1, N, b, c);

			/*float rate = (float)c / src[b];
			if (rate == 0)
				rate = 1;
			else
				src[b] = c;
			updateTree(1, 1, N, b, rate);*/
		}
		else if (a == 2)
		{
			ll ans = getMul(1, 1, N, b, c)%MOD;
			printf("%lld\n", ans);
		}
	}


	return 0;
}