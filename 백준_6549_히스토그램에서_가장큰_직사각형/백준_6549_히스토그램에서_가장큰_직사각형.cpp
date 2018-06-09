/*
(1)���� ���� ���̸� ã�Ƽ�, ������ ���ۺ��� �������� ���̸� ���Ѵ�.
(2)������ �ΰ��� ������, ���� ������ �ݺ��ϸ鼭 ���� ū ���̸� ���Ѵ�.
- ���� ���� ���̸� ã�°����� ���׸�Ʈ Ʈ���� �̿��ؼ� ���Ͽ��� logN�ð����� ���� �� �ִ�.
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

//���׸�Ʈ Ʈ������ ���̰� �������� �迭����� [�ε���]�� ����Ǿ� ������ �����Ұ�
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

		//���������� index ����
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

	//�̺κ��� �� �����ص���
	if (leftIdx == INF)
		return rightIdx;
	else if (rightIdx == INF)
		return leftIdx;
	else
	{
		//min���� �����Ͽ��� �Ѵ�
		if (hSrc[leftIdx] < hSrc[rightIdx])	//Ʈ������ �ε����� ����Ǿ� �����Ƿ� �� ���� ������ ���Ͽ��� �Ѵ�.
			return leftIdx;
		else
			return rightIdx;
	}
}


ll getMaxArea(int left, int right)
{
	//����������
	int minIdx = getMinIdx(1, 1, N, left, right);

	//��ü������ �ִ�������ϰ�
	ll area = (right - left + 1)*hSrc[minIdx];

	//���� ����
	ll areaLeft;
	if (left <= minIdx - 1)
	{
		areaLeft = getMaxArea(left, minIdx - 1);
		if (areaLeft > area)
			area = areaLeft;
	}

	//������ ����
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