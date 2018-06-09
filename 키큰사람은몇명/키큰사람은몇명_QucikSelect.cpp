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

using namespace std;

int gArrSrc[300001];
int gArrTmp[300002];	//�������� key�� �����ؾ� �ϹǷ� �Ѱ���

int nTestCnt;
int N, Q, a, b, x;

void Swap(int& a, int& b)
{
	int tmp;
	tmp = a; a = b; b = tmp;
}

int Partition(int start, int end)
{
	int left, right, size, key;

	key = x;							//���Ƿ� �迭�� ������ �����͸� �������� ��Ҵ�

	if (start == end)
	{
		if (gArrTmp[start] > key)
			return 1;
		else
			return 0;
	}

	for (left = start, right = end;; left++, right--)
	{
		while (gArrTmp[left] > key) left++;		//�迭 ������ ���غ��� �������� �ִ��� ã�´�
		while (gArrTmp[right] <= key) right--;	//�迭 ������ ���غ��� ū ���� �ִ��� ã�´�
		
		if (right <= left)
			break;
		else
			Swap(gArrTmp[left], gArrTmp[right]);
	}

	//Swap(gArrTmp[left], gArrTmp[end]);	//���ذ��� ��ȯ. ���⼭ ��ȯ�۾��ϸ� Ÿ�Ӿƿ� �߻���

	return left-start;
}

int main()
{
	char* buff;

	freopen("test_input_tall_8.txt", "r", stdin);

	int startTime = clock();

	cin >> nTestCnt;
	for (int testcase = 0; testcase < nTestCnt; testcase++)
	{
		memset(gArrSrc, 0x00, sizeof(gArrSrc));
		memset(gArrTmp, 0x00, sizeof(gArrTmp));

		cin >> N;
		for (int i = 1; i <= N; i++)
			scanf("%d", &gArrSrc[i]);

		cin >> Q;

		int size;
		int ans;


		printf("#%d ", testcase + 1);
		
		buff = new char[Q * 10 + 1];				//10 = 9(�ڸ���) +1(" "), 1=null terminated string
		memset(buff, 0, sizeof(char)*Q * 10 + 1);
		int len = 0;

		for (int i = 1; i <= Q; i++)
		{
			scanf("%d %d %d", &a, &b, &x);
			size = b - a + 1;

			memcpy(&gArrTmp[a], &gArrSrc[a], sizeof(int)*size);

			//printf("%d ", Partition(a, b));
			len += sprintf(buff+len, "%d ", Partition(a, b));
			memset(&gArrTmp[a], 0x00, sizeof(int)*size);
		}
		printf("#%d %s\n", testcase+1, buff);
		delete[] buff;
	}

	printf("Elapsed Time(Quick Select) : %d ms", clock() - startTime);
	return 0;
}