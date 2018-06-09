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


//구간곱 세그먼트트리의 업데이트의 경우 구간합처럼 diff만을 더할수가 없다.
//예를들어 어떤 리프노드의 값을 4에서 6으로 변경하는 경우를 생각해보자.
//구간합에서는 기존값과의 차이인 diff==2를 관련된 노드에 모두 더하면 되었지만 곱에서는 그럴수가 없다.
//변화율인 6/4를 각 노드에 다 곱해줄것인가? 이건 논리적으로 가능하다. 단 분수연산을 하였을 경우에만 가능하고 소수연산을 하게되면 오차가 발생하게 된다.
//하지만 컴퓨터는 나눗셈 연산에서 오차를 수반하게 되므로 정확한 값을 얻을 수 없다.
//그러면 어떻게 할 것인가? 그래 그냥 깔끔하게 원래값을 바꾸어주고 새롭게 빌드하는게 속 편하겠다.
//그래서 아래와 같이 마치 buildTree()와 유사한 형태의 update()함수를 사용하게 된다.
ll updateTree(int node, int start, int end, int index, ll val)
{
	if (index<start || end<index)
		return tree[node];	//현재노드 반환

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
		return 1;		//이부분이 곱 구할때 중요하다!!!!!!!
	
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