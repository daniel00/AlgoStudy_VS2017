#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> src(100001);
vector<int> tree[4*100001];	//�� ������ ���׸�Ʈ Ʈ���� �迭�� �����Ͽ��� �ϹǷ�, �����迭�� �����Ѵ�. ũ��� [���׸�ƮƮ������==4*�ҽ�����]


void buildTree(int node, int start, int end)
{
	if (start == end) //��������̸�
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