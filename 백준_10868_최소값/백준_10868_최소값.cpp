#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

typedef long long ll;

vector<ll> src(0);
vector<ll> tree(0);

const int INF = (int)1e9 + 10;
char* buff;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

ll buildTree(int node, int start, int end)
{
	if (start == end)
		return tree[node] = src[start];
	
	return tree[node] = min(buildTree(node * 2, start, (start + end) / 2), buildTree(node * 2 + 1, (start + end) / 2 + 1, end));
}

ll updateTree(int node, int start, int end, int index, int val)
{
	if (index < start || end < index)
		return tree[node];

	if (start == end)
		return tree[node] = val;

	return tree[node] = min(updateTree(node * 2, start, (start + end) / 2, index, val), updateTree(node * 2 + 1, (start + end) / 2+1, end, index, val));
}

ll getMin(int node, int start, int end, int left, int right)
{
	if (right < start || end < left)
		return INF;

	if (left <= start && end <= right)
		return tree[node];

	return min(getMin(node*2, start, (start+end)/2, left, right) , getMin(node*2+1, (start+end)/2+1, end, left, right));
}

int main()
{
	//test
	/*src = { 0,2,3,5,1 };
	tree.resize(5 * 4 + 1);
	buildTree(1, 1, 4);
	updateTree(1, 1, 4, 2, 4);
	printf("%d\n", getMin(1, 1, 4, 2, 4));*/

	freopen("sample_input.txt", "r", stdin);

	int N, M;
	int a, b;

	scanf("%d %d", &N, &M);
	src.resize(N + 1);
	tree.resize(N * 4 + 1);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &src[i]);
	}
	buildTree(1, 1, N);


	buff = new char[M * 10 + 1];				//10 = 9(ÀÚ¸®¼ö) +1(" "), 1=null terminated string
	memset(buff, 0, sizeof(char)*M * 10 + 1);
	int len = 0;

	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d", &a, &b);
		//printf("%d\n", getMin(1, 1, N, a, b));
		len += sprintf(buff+len, "%d\n", getMin(1, 1, N, a, b));
	}
	printf("%s", buff);

	return 0;
}
