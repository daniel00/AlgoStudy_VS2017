/*
문제
어떤 N개의 수가 주어져 있다. 그런데 중간에 수의 변경이 빈번히 일어나고 그 중간에 어떤 부분의 합을 구하려 한다. 
만약에 1,2,3,4,5 라는 수가 있고, 3번째부터 4번째 수에 6을 더하면 1, 2, 9, 10, 5가 되고, 여기서 2번째부터 5번째까지 합을 구하라고 한다면 26을 출력하면 되는 것이다. 
그리고 그 상태에서 1번째부터 3번째 수에 2를 빼고 2번째부터 5번째까지 합을 구하라고 한다면 22가 될 것이다.

입력
첫째 줄에 수의 개수 N(1<=N<=1,000,000)과 M(1<=M<=10,000), K(1<=k<=10,000) 가 주어진다. 
M은 수의 변경이 일어나는 회수이고, K는 구간의 합을 구하는 회수이다. 
그리고 둘째 줄부터 N+1번째 줄까지 N개의 수가 주어진다. 
그리고 N+2번째 줄부터 N+M+K+1번째 줄까지 세 개의 정수 a,b,c 또는 a,b,c,d가 주어지는데, 
a가 1인 경우 b번째 수부터 c번째 수에 d로 더하고, a가 2인 경우에는 b부터 c까지의 합을 구하여 출력하면 된다.

출력
첫째 줄부터 K줄에 걸쳐 구한 구간의 합을 출력한다. (단 정답은 long long 범위를 넘지 않는다)
*/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6;
vector<ll> src;
vector<ll> tree;	//대략4배하면 트리사이즈로 충분함
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
		//(1)현재노드에 Lazy를 반영해준다(이번 문제에서는 더하기)
		tree[node] += (end - start + 1)*lazy[node];

		//(2)리프노드가 아닐경우, 하위 트리에 lazy를 전파해 준다
		if (start != end)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		//(3)현재 노드의 Lazy를 0으로 리셋한다
		lazy[node] = 0;
	}
}

//qleft : query left, qright : query right
ll getSum(int node, int start, int end, int qleft, int qright)
{
	checkLazy(node, start, end);

	if (qright < start || end < qleft)
		return 0;

	if (qleft <= start && end <= qright) //재귀적으로 더 들어가볼 필요가 없다
		return tree[node];

	return getSum(node * 2, start , (start + end) / 2, qleft, qright) + getSum(node * 2 + 1, (start + end) / 2 + 1, end, qleft, qright);
}



//uleft, uright : update left, right
void updateRange(int node, int start, int end, int uleft, int uright, ll diff)
{
	//lazy가 있는지 점검
	checkLazy(node, start, end);

	//현재 노드가 업데이트 영역과 겹치지 않으면 그냥 리턴
	if (uright < start || end < uleft)
		return;

	/*************************************************************************************/
	//Lazy Propagation의 핵심
	//대표구간노드 대해서만 업데이트를 수행하고, 서브트리에는 표시만 해준다!!!!!!
	//대표구간노드 : 업데이트 영역에 완전히 포함되는 노드
	if (uleft <= start && end <= uright)
	{
		//대표구간 업데이트
		tree[node] += (end - start + 1)*diff;		

		//리프노드가 아니면, 좌우 하위트리에 Lazy표시
		if (start != end)
		{
			lazy[node * 2] += diff;
			lazy[node * 2+1] += diff;
		}
		return;
	}
	/*************************************************************************************/


	//대표구간이 아니였을 경우 좌우하위트리 업데이트
	updateRange(node*2, start, (start + end) / 2, uleft, uright, diff);
	updateRange(node*2+1, (start + end) / 2 + 1, end, uleft, uright, diff);

	//위의 하위트리 업데이트가 끝나서 리턴하면 현재 노드의 값을 좌우하위 노드의 값으로 업데이트
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