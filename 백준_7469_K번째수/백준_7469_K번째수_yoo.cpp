#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> src(100001);
vector<int> tree[4*100001];	//이 문제의 세그먼트 트리는 배열을 저장하여야 하므로, 동적배열로 선언한다. 크기는 [세그먼트트리개수==4*소스개수]


void buildTree(int node, int start, int end)
{
	if (start == end) //리프노드이면
	{
		tree[node] = vector<int>(1);
		tree[node][0] = src[start];
		return;
	}
	buildTree(node * 2, start, (start + end) / 2);
	buildTree(node * 2 + 1, (start + end) / 2 + 1, end);
	tree[node].resize(end - start + 1);
	merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
}

void getLessThenCnt()
{

}

int main()
{

	return 0;
}