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
	if (lazy[node] != 0) //1이면 반전을 수행하라는 의미이다
	{
		//현재노드에 lazy 적용
		tree[node] = (end - start + 1) - tree[node];

		//리프노드가 아니면 좌우 노드에 lazy전파
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}

		//재실행 방지를 위해서 리셋
		lazy[node] = 0;
	}
}

int updateRange(int node, int start, int end, int uleft, int uright)
{
	updateLazy(node, start, end);

	//업데이트 영역에 포함되지 않으면 현재 노드값 리턴
	if (uright < start || end < uleft)
		return tree[node];
	
	//업데이트 영역에 노드가 완전히 포함될 경우에는, 대표노드에 대해서만 업데이트를 수행하고 lazy를 좌우 서브트리에 표시
	if (uleft <= start && end <= uright)
	{
		tree[node] = (end - start + 1) - tree[node]; //대표노드에 대해서만 업데이트(반전) 수행

		//리트노드가 아닐경우, 좌우트리에 lazy 전파
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}
		return tree[node];
	}

	//그외 업데이트 영역이 노드와 일부마 겹치는 경우, 좌우서브트리 점검
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
	//printf("%d\n", getSum(1, 1, 4, 1, 4));	// 2~3영역중 스위치 켜진개수는 1

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