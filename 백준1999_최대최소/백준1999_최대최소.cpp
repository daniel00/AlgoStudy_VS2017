#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
#include <functional>
#include <time.h>

using namespace std;

int gArrMat[251][251];
int gArrAns[251][251];			//한번 구한 값을 중복계산하지 않도록 저장하여 놓는 Look Up Table


int GetMaxMinDiff(int nStartRow, int nStartCol, int nSize)
{
	int min = 999;
	int max = 0;

	for (int row = nStartRow; row<nStartRow + nSize; row++)
	{
		for (int col = nStartCol; col<nStartCol + nSize; col++)
		{
			//min
			if (gArrMat[row][col]<min)
				min = gArrMat[row][col];
			//max
			if (gArrMat[row][col]>max)
				max = gArrMat[row][col];
		}
	}

	//나중에 중복계산 방지를 위해서 answer를 저장
	gArrAns[nStartRow][nStartCol] = max - min;

	return gArrAns[nStartRow][nStartCol];
}

int main()
{
	int N;					//행수(=열수)
	unsigned int K;			//질문개수 : 100000(십만개)까지 나오므로 unsigned int
	int B;					//행렬크기
	int StartRow, StartCol;
	int result;

	freopen("sample_input.txt", "r", stdin);
	int startTime = clock();

	memset(gArrMat, 0x00, sizeof(gArrMat));
	memset(gArrAns, -1, sizeof(gArrAns));		//max-min이 0이 될 수 있으므로 -1로 초기화


												//-----------------------------------------------------------------------------------------------
												//입력 처리
	cin >> N >> B >> K;
	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			//cin>>gArrMat[row][col];			
			scanf("%d", &gArrMat[row][col]);
		}
	}
	//-----------------------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------------------------
	//부분행렬 최대/최소 계산
	char* buff = new char[K * 5 + 1];				
	memset(buff, 0, sizeof(char)*K * 5 + 1);
	int len = 0;

	for (unsigned int i = 0; i<K; i++)
	{
		//cin>>StartRow>>StartCol;					//cin 사용시 시간초과 발생함에 유의!!!!!
		scanf("%d %d", &StartRow, &StartCol);

		if (gArrAns[StartRow][StartCol] != -1)				//중복문제의 경우 반복계산하지 않고, 룩업테이블 기존 테이터를 이용
		{
			//cout<<gArrAns[StartRow][StartCol]<<"\n";
			//printf("%d\n", gArrAns[StartRow][StartCol]);
			len += sprintf(buff+len, "%d\n", gArrAns[StartRow][StartCol]);
		}
		else
		{
			GetMaxMinDiff(StartRow, StartCol, B);
			////cout<<result<<"\n";
			//printf("%d\n", gArrAns[StartRow][StartCol]);
			len += sprintf(buff+len, "%d\n", gArrAns[StartRow][StartCol]);
		}
	}
	printf("%s", buff);
	delete[] buff;
	//-----------------------------------------------------------------------------------------------
	printf("\nElapsed Time : %d ms", clock() - startTime);			//option



	return 0;
}
