#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

vector<ll> src(0);
vector<ll> tree(0);

int N, M, K;
int a, b;
ll c;


//�����ǥ�� node1�� ��籸���� start~end�� �յ����͸� �������ְԲ� ����°��̴�. buildTree(1, start, end)
//��������� ������带 ���������� ��� ���Եǰ�, ������带 ������ ��带 �����ϸ鼭 �����ϰ� �ȴ�.
//������ ���������� ����Ǹ鼭 ���� ���� ��尡 ����ȴ�(��������� �� �����͸� �����鼭)
ll buildTree(int node, int start, int end)
{
	if (start == end)
		return tree[node] = src[start];				//���� ��尡 ��������� ���������͸� Ʈ���� �����ϰ� �� ���� �����Ѵ�. ������忡�� �� ���� �����ϰ� �� ���̴�
	else
	{
		//�¿� ����� �� ����							//������尡 �ƴϸ� ����/������ ������ �����ϰ� �ȴ�
		return tree[node] = buildTree(node * 2, start, (start + end) / 2) + buildTree(node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

void updateTree(int node, int start, int end, int index, ll diff)
{
	if (index<start || end<index)					//���� ����� start~end ��������, �����ϰ��� �ϴ� index�� ���ԵǾ� ���� �ʴٸ� �׳� �����Ѵ�
		return;
	else											//start~end������ ���ԵǾ� ������
	{
		tree[node] += diff;							//���� node�� ���� ��������ְ�,
		if (start != end)							//������尡 �ƴѰ�쿡�� ����/������ ��带 �����Ѵ�.
		{
			updateTree(node * 2, start, (start + end) / 2, index, diff);
			updateTree(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
		}
	}
}

long long getSum(int node, int start, int end, int left, int right)
{
	if (right < start || end < left) //���� node�� start~end������, ���ϰ��� �ϴ� ������ �ϳ��� �����ϰ� ���� �ʴٸ� �׳� �����Ѵ�
		return 0;

	if (left <= start && end <= right) //���� node�� start~end������ , ���ϰ����ϴ� ������ ������ ���ԵǸ� ���� ����� �������� �����Ѵ�
		return tree[node];
	
	//���� node�� start~end������ , ���ϰ����ϴ� 
	return getSum(node * 2, start, (start + end) / 2, left, right) + getSum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}


int main()
{
	//test
	//src = {0,1,2,3,4,5 };
	//tree.resize(src.size() * 4 + 1);
	////src[5] = 6;
	////updateTree(1, 0, 5, 5, 1);			//5-->6
	//buildTree(1, 1, src.size()-1);	//���� node ��ȣ�� 1���� �����Կ� ����(node*2�� �����Ͽ��� �ϹǷ� 0�� �Ǹ� �ȵȴ�)
	//printf("%d\n", getSum(1,0,5,0,5));

	freopen("sample_input.txt", "r", stdin);

	scanf("%d %d %d", &N, &M, &K);

	src.resize(N+1);
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	tree.resize(tree_size+1);

	for (int i = 1; i <= N; i++)
	{
		scanf("%lld", &src[i]);
	}
	buildTree(1,1,N);

	for (int i = 1; i <= M+K; i++)
	{
		scanf("%d %d %lld", &a, &b, &c);
		if (a == 1)
		{
			ll diff = c - src[b];
			src[b] = c;							//������ diff ����� ���ؼ� source���� �������־�� �Ѵ�
			updateTree(1, 1, N, b, diff);		//tree�� update�Ѵ�
		}
		else if (a == 2)
		{
			printf("%lld\n", getSum(1, 1, N, b, c));
		}
	}


	return 0;
}