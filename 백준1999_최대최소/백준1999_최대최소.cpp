#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
#include <functional>
#include <time.h>

using namespace std;

int gArrMat[251][251];
int gArrAns[251][251];			//�ѹ� ���� ���� �ߺ�������� �ʵ��� �����Ͽ� ���� Look Up Table


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

	//���߿� �ߺ���� ������ ���ؼ� answer�� ����
	gArrAns[nStartRow][nStartCol] = max - min;

	return gArrAns[nStartRow][nStartCol];
}

int main()
{
	int N;					//���(=����)
	unsigned int K;			//�������� : 100000(�ʸ���)���� �����Ƿ� unsigned int
	int B;					//���ũ��
	int StartRow, StartCol;
	int result;

	freopen("sample_input.txt", "r", stdin);
	int startTime = clock();

	memset(gArrMat, 0x00, sizeof(gArrMat));
	memset(gArrAns, -1, sizeof(gArrAns));		//max-min�� 0�� �� �� �����Ƿ� -1�� �ʱ�ȭ


												//-----------------------------------------------------------------------------------------------
												//�Է� ó��
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
	//�κ���� �ִ�/�ּ� ���
	char* buff = new char[K * 5 + 1];				
	memset(buff, 0, sizeof(char)*K * 5 + 1);
	int len = 0;

	for (unsigned int i = 0; i<K; i++)
	{
		//cin>>StartRow>>StartCol;					//cin ���� �ð��ʰ� �߻��Կ� ����!!!!!
		scanf("%d %d", &StartRow, &StartCol);

		if (gArrAns[StartRow][StartCol] != -1)				//�ߺ������� ��� �ݺ�������� �ʰ�, ������̺� ���� �����͸� �̿�
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
