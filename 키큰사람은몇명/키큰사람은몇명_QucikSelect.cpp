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

using namespace std;

int gArrSrc[300001];
int gArrTmp[300002];	//마지막에 key를 복사해야 하므로 한개더

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

	key = x;							//임의로 배열의 마지막 데이터를 기준으로 잡았다

	if (start == end)
	{
		if (gArrTmp[start] > key)
			return 1;
		else
			return 0;
	}

	for (left = start, right = end;; left++, right--)
	{
		while (gArrTmp[left] > key) left++;		//배열 좌측에 기준보다 작은수가 있는지 찾는다
		while (gArrTmp[right] <= key) right--;	//배열 우측에 기준보다 큰 수가 있는지 찾는다
		
		if (right <= left)
			break;
		else
			Swap(gArrTmp[left], gArrTmp[right]);
	}

	//Swap(gArrTmp[left], gArrTmp[end]);	//기준값과 교환. 여기서 교환작업하면 타임아웃 발생함

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
		
		buff = new char[Q * 10 + 1];				//10 = 9(자리수) +1(" "), 1=null terminated string
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