/*
(1)가장 낮은 높이를 찾아서, 구간의 시작부터 끝까지의 넓이를 구한다.
(2)구간을 두개로 나누고, 위의 과정을 반복하면서 가장 큰 넓이를 구한다.
- 가장 작은 높이를 찾는과정은 세그먼트 트리를 이용해서 구하여야 logN시간만에 구할 수 있다.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long long ll;
const int MAXN = 100000;
const int INF = -1;

int hSrc[MAXN+1];
int tree[4 * MAXN + 1];

ll areaMax = 0;
int N;

//세그먼트 트리에는 높이가 가장작은 배열요소의 [인덱스]가 저장되어 있음에 유의할것
void buildTree(int node, int start, int end)
{
	if (start == end)
	{
		tree[node] = start;
		return;
	}
	else
	{
		int mid = (start + end)/2;
		buildTree(node * 2, start, mid);
		buildTree(node * 2 + 1, mid + 1, end);

		//작은높이의 index 저장
		if (hSrc[tree[node * 2]] < hSrc[tree[node * 2 + 1]])
			tree[node] = tree[node * 2];
		else
			tree[node] = tree[node * 2 + 1];

		return;
	}
}

int getMinIdx(int node, int start, int end, int qleft, int qright)
{
	if(qright<start || end<qleft)
		return INF;

	if (qleft <= start && end <= qright)
		return tree[node];

	int mid = (start + end) / 2;
	int leftIdx = getMinIdx(node * 2, start, mid, qleft, qright);
	int rightIdx = getMinIdx(node * 2 + 1, mid + 1, end, qleft, qright);

	//이부분을 잘 염두해두자
	if (leftIdx == INF)
		return rightIdx;
	else if (rightIdx == INF)
		return leftIdx;
	else
	{
		//min값을 점검하여야 한다
		if (hSrc[leftIdx] < hSrc[rightIdx])	//트리에는 인덱스만 저장되어 있으므로 그 값은 별도로 비교하여야 한다.
			return leftIdx;
		else
			return rightIdx;
	}
}


ll getMaxArea(int left, int right)
{
	//구간나누고
	int minIdx = getMinIdx(1, 1, N, left, right);

	//전체영역의 최대면적구하고
	ll area = (right - left + 1)*hSrc[minIdx];

	//왼쪽 면적
	ll areaLeft;
	if (left <= minIdx - 1)
	{
		areaLeft = getMaxArea(left, minIdx - 1);
		if (areaLeft > area)
			area = areaLeft;
	}

	//오른쪽 면적
	ll areaRight;
	if (minIdx + 1 <= right)
	{
		areaRight = getMaxArea(minIdx + 1, right);
		if (areaRight > area)
			area = areaRight;
	}
	return area;
}


int main()
{
	//test
	/*hSrc[1] = 1;
	hSrc[2] = 2;
	hSrc[3] = 3;
	hSrc[4] = 4;
	buildTree(1, 1, 4);
	printf("%d\n", getMinIdx(1, 1, 4, 1, 3));*/

#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	
	while (1)
	{
		scanf("%d", &N);
		if (N == 0)
			break;

		memset(hSrc, 0, sizeof(hSrc));
		memset(tree, 0, sizeof(tree));

		for (int i = 1; i <= N; i++)
			scanf("%d", &hSrc[i]);

		buildTree(1, 1, N);

		printf("%lld\n", getMaxArea(1, N));
	}
	
	
	return 0;
}