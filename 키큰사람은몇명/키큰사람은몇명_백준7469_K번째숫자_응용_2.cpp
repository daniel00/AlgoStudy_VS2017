/*
ũ�� N�� �迭��, ���� a, b�� ���ؼ� x���� ū ������ ������ ����϶�
���ѽð� : 2��, �޸�:128MB

�Է�
Test Case
N : �迭�� ũ��(1~300000)
N���� ���Ұ� �������� ���еǾ� �־�����.
Q : ������ ��(1~300000)
���� Q�ٿ� ���ļ� a, b, x (1~10^9)

ex)
�Է�
1
5
185 196 200 175 195
4
1 3 190
2 4 197
3 5 180
1 5 250

���
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
vector<int> s[4 * MAXN+1];	//�� ������ ���׸�Ʈ Ʈ���� �迭�� �����Ͽ��� �ϹǷ�, �����迭�� �����Ѵ�. ũ��� [���׸�ƮƮ������==4*�ҽ�����]

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

	//�¿��ڽ� �迭�� ũ�⸸ŭ(end-start+1) �迭�� �Ҵ� �� ��
	//�¿� �ڽĹ迭�� merge()�Ѵ�. �̶� merge()�Լ����� ���ĵ� �Բ� ����ȴ�.
	s[id].resize(r - l + 1, 0);
	merge(s[id << 1].begin(), s[id << 1].end(), s[id << 1 | 1].begin(), s[id << 1 | 1].end(), s[id].begin());
}

int getLessThanCnt(int x, int y, int k, int id = 1, int l = 0, int r = N - 1)
{
	if (r<x || y<l)
		return 0;

	if (x <= l && r <= y)
		return upper_bound(s[id].begin(), s[id].end(), k) - s[id].begin(); //k���� �۰ų� ���� ���� [����]�� �����Ѵ�. ���ĵǾ� �����Ƿ� �˻��� �迭�� �ε����� �� ������.

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
			ans = size - getLessThanCnt(a,b,x); //������ ��ü��� �������� x���� ���� ������ ���� �� x���� ū ����

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