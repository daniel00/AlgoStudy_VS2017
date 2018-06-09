#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "time.h"

using namespace std;

void DFS(int nStartVtxNum);

int nTotVertex;
int nTotEdge;
int nStartVertex;

char arrVtxMat[1000 + 1][1000 + 1]; //인접행렬, I will use from 1 base of matrix, so size is 1000+1
char arrIsVisit[1000 + 1];

int main()
{
	nTotVertex=0;
	nTotEdge=0;
	nStartVertex=0;

	int nRow;
	int nCol;

	//read input file
	freopen("02_test_input.txt", "r", stdin);
	cin >> nTotVertex;
	cin >> nTotEdge;
	cin >> nStartVertex;


	memset(arrVtxMat,	0x00, sizeof(char)* 1001 * 1001);
	memset(arrIsVisit,	0x00, sizeof(char)* 1001);

	for (int i = 1; i <= nTotEdge; i++)
	{
		cin >> nRow;
		cin >> nCol;

		arrVtxMat[nRow][nCol] = arrVtxMat[nCol][nRow] = 1;
	}

	printf("%d ", nStartVertex);
	DFS(nStartVertex);	//재귀적으로 동작하면서 모든 버텍스를 경유하게 된다.

	printf("\n");
	printf("BFS Result here\n");

	//system("pause"); //remain to open console window 

	return 0;
}

void DFS(int nStartVtxNum)
{
	int row = nStartVtxNum;

	arrIsVisit[nStartVtxNum] = 1;

	for (int col = 1; col <= nTotVertex; col++)
	{
		if (arrVtxMat[row][col]==1 && arrIsVisit[col]==0)	//인접행렬이 1이고, 방문하지 않았던 버텍스인지 점검
		{
			printf("%d ",col);
			//printf("%d에서 %d로 이동\n", nStartVtxNum, col);
			DFS(col);
		}
	}

	return;		//재귀함수의 리턴을 표현하기 위하여 명시적으로 표시하였다
}
