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


//빌드목표는 node1이 모든구간인 start~end의 합데이터를 가지고있게끔 만드는것이다. buildTree(1, start, end)
//재귀적으로 리프노드를 만날때까지 계속 들어가게되고, 리프노드를 만나면 노드를 빌드하면서 리턴하게 된다.
//리턴이 연쇄적으로 수행되면서 점차 상위 노드가 빌드된다(하위노드의 합 데이터를 가지면서)
ll buildTree(int node, int start, int end)
{
	if (start == end)
		return tree[node] = src[start];				//현재 노드가 리프노드라면 원본데이터를 트리에 복사하고 그 값을 리턴한다. 상위노드에서 이 값을 누적하게 될 것이다
	else
	{
		//좌우 노드의 합 저장							//리프노드가 아니면 왼쪽/오른쪽 노드들을 빌드하게 된다
		return tree[node] = buildTree(node * 2, start, (start + end) / 2) + buildTree(node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

void updateTree(int node, int start, int end, int index, ll diff)
{
	if (index<start || end<index)					//현재 노드의 start~end 범위내에, 변경하고자 하는 index가 포함되어 있지 않다면 그냥 리턴한다
		return;
	else											//start~end범위에 포함되어 있으면
	{
		tree[node] += diff;							//현재 node의 값을 변경시켜주고,
		if (start != end)							//리프노드가 아닌경우에는 왼쪽/오른쪽 노드를 점검한다.
		{
			updateTree(node * 2, start, (start + end) / 2, index, diff);
			updateTree(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
		}
	}
}

long long getSum(int node, int start, int end, int left, int right)
{
	if (right < start || end < left) //현재 node의 start~end범위가, 구하고자 하는 범위를 하나도 포함하고 있지 않다면 그냥 리턴한다
		return 0;

	if (left <= start && end <= right) //현재 node의 start~end범위가 , 구하고자하는 범위에 완전히 포함되면 현재 노드의 합정보를 리턴한다
		return tree[node];
	
	//현재 node의 start~end범위가 , 구하고자하는 
	return getSum(node * 2, start, (start + end) / 2, left, right) + getSum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}


int main()
{
	//test
	//src = {0,1,2,3,4,5 };
	//tree.resize(src.size() * 4 + 1);
	////src[5] = 6;
	////updateTree(1, 0, 5, 5, 1);			//5-->6
	//buildTree(1, 1, src.size()-1);	//최초 node 번호는 1부터 시작함에 유의(node*2를 수행하여야 하므로 0이 되면 안된다)
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
			src[b] = c;							//다음번 diff 계산을 위해서 source값도 변경해주어야 한다
			updateTree(1, 1, N, b, diff);		//tree도 update한다
		}
		else if (a == 2)
		{
			printf("%lld\n", getSum(1, 1, N, b, c));
		}
	}


	return 0;
}