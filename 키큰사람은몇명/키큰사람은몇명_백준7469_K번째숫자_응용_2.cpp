/*
크기 N인 배열중, 구간 a, b에 대해서 x보다 큰 원소의 개수를 출력하라
제한시간 : 2초, 메모리:128MB

입력
Test Case
N : 배열의 크기(1~300000)
N개의 원소가 공백으로 구분되어 주어진다.
Q : 질문의 수(1~300000)
이후 Q줄에 걸쳐서 a, b, x (1~10^9)

ex)
입력
1
5
185 196 200 175 195
4
1 3 190
2 4 197
3 5 180
1 5 250

출력
#1 2 1 2 0

*/


#include <iostream>
#include <cstdio>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm> //sort, merge

using namespace std;

const int MAXN = 300000;
vector<int> src(MAXN+1);
vector<int> s[4 * MAXN+1];	//이 문제의 세그먼트 트리는 배열을 저장하여야 하므로, 동적배열로 선언한다. 크기는 [세그먼트트리개수==4*소스개수]

int nTestCnt;
int N, Q, a, b, x;

void build(int id = 1, int l = 0, int r = N - 1)
{
	if (l == r) {
		s[id] = vector<int>(1);
		s[id][0] = src[l];
		return;
	}

	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);

	//좌우자식 배열의 크기만큼(end-start+1) 배열을 할당 한 후
	//좌우 자식배열을 merge()한다. 이때 merge()함수에서 정렬도 함께 수행된다.
	s[id].resize(r - l + 1, 0);
	merge(s[id << 1].begin(), s[id << 1].end(), s[id << 1 | 1].begin(), s[id << 1 | 1].end(), s[id].begin());
}

int getLessThanCnt(int x, int y, int k, int id = 1, int l = 0, int r = N - 1)
{
	if (r<x || y<l)
		return 0;

	if (x <= l && r <= y)
		return upper_bound(s[id].begin(), s[id].end(), k) - s[id].begin(); //k보다 작거나 같은 수의 [개수]를 리턴한다. 정렬되어 있으므로 검색된 배열의 인덱스가 곧 개수다.

	int mid = (l + r) >> 1;
	return getLessThanCnt(x, y, k, id << 1, l, mid) + getLessThanCnt(x, y, k, id << 1 | 1, mid + 1, r);
}


int main()
{
	char* buff;

	freopen("test_input_tall_8.txt", "r", stdin);

	int startTime = clock();

	cin >> nTestCnt;
	FILE* file = fopen("answer_8_file_SegTree.txt", "w");
	for (int testcase = 0; testcase < nTestCnt; testcase++)
	{
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &src[i]);
		}
		build();

		cin >> Q;
		int size;
		int ans;

		//printf("#%d ", testcase + 1);
		fprintf(file, "#%d ", testcase + 1);
		for (int i = 1; i <= Q; i++)
		{
			scanf("%d %d %d", &a, &b, &x);
			size = b - a + 1;
			ans = size - getLessThanCnt(a,b,x); //구간의 전체요소 개수에서 x보다 작은 개수를 빼면 곧 x보다 큰 개수

			//printf("%d ", ans);
			fprintf(file, "%d ", ans);
		}
		//printf("\n");
		fprintf(file, "\n");
	}

	printf("Elapsed Time(Segment Tree) : %d ms", clock() - startTime);
	
	fprintf(file, "\n");
	fprintf(file, "Elapsed Time(Segment Tree) : %d ms\n", clock() - startTime);
	fprintf(file, "Elapsed Time(BIT)          : 1851 ms\n");
	fprintf(file, "Elapsed Time(Quick Select) : 65570 ms\n");

	return 0;
}