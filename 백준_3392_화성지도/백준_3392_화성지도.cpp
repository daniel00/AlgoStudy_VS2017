/*
plane sweeping + 세그먼트트리로 푼다


넓이를 구하는데에는 1인 세그먼트 트리의 개수만 알고있으면 되므로,
해당노드를 cnt하는 cnt변수를 별도로 하나두어서


*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct STRUCT_RECT
{
	int x;
	int y1;
	int y2;
	bool IsStart;	//start, end
};

typedef long long ll;
vector<STRUCT_RECT> vp;	//point


const int MAXN = 30000;
int tree[MAXN * 4 + 1];
int cnt[MAXN * 4 + 1];

int N;

bool cmp(STRUCT_RECT &a, STRUCT_RECT &b)
{
	return a.x < b.x;
}

void updateRange(int node, int start, int end, int uleft, int uright, int val)
{
	if (uright<start || end<uleft)
		return;

	if (uleft <= start && end <= uright)
	{
		//별도의 카운트값을 업데이트 한다.
		cnt[node] += val;
	}
	else
	{
		int mid = (start + end) / 2;
		updateRange(node * 2, start, mid, uleft, uright, val);
		updateRange(node * 2 + 1, mid + 1, end, uleft, uright, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	
	//실제로 tree[node]의 값은 아래의 조건으로 구현한다
	if (cnt[node] > 0)
		tree[node] = end - start + 1;
	else
	{
		if (start == end)
			tree[node] = 0;
		else
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif

	scanf("%d", &N);

	STRUCT_RECT s1, s2;
	for (int i = 0; i<N; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		s1.x = x1, s1.y1 = y1, s1.y2 = y2, s1.IsStart = true;
		s2.x = x2, s2.y1 = y1, s2.y2 = y2, s2.IsStart = false;

		vp.push_back(s1);
		vp.push_back(s2);
	}

	//x1을 기준으로 정렬
	sort(vp.begin(), vp.end(), cmp);

	ll area = 0;
	int prevX = 0;
	int left, right;

	for (int i = 0; i < vp.size(); i++)
	{
		left  = vp[i].y1;
		right = vp[i].y2-1;	//y-range 1~3 => tree node num : 1~2

		int width = vp[i].x - prevX;
		int height = tree[1]; //전체구간중 1보다 큰 구간의 개수

		area += width*height;

		if(vp[i].IsStart)
			updateRange(1, 0, MAXN, left, right, 1);
		else
			updateRange(1, 0, MAXN, left, right, -1);

		prevX = vp[i].x;
	}
	
	printf("%lld", area);

	return 0;
}