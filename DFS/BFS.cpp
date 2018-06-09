#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

void BFS(int nStartVtxNum);

int nTotVertex;
int nTotEdge;
int nStartVertex;

char arrVtxMat[1000 + 1][1000 + 1]; //인접행렬, I will use from 1 base of matrix, so size is 1000+1
char arrIsVisit[1000 + 1];
queue<int> q;

int* pPath = NULL;
int nIndex = 0;

int main()
{
	nTotVertex = 0;
	nTotEdge = 0;
	nStartVertex = 0;

	int nRow;
	int nCol;

	//read input file
	freopen("02_test_input.txt", "r", stdin);
	
	cin >> nTotVertex;
	cin >> nTotEdge;
	cin >> nStartVertex;

	memset(arrVtxMat, 0x00, sizeof(char)* 1001 * 1001);
	memset(arrIsVisit, 0x00, sizeof(char)* 1001);

	for (int i = 1; i <= nTotEdge; i++)
	{
		cin >> nRow;
		cin >> nCol;

		arrVtxMat[nRow][nCol] = arrVtxMat[nCol][nRow] = 1;
	}

	BFS(nStartVertex);

	return 0;
}

void BFS(int nStartVtxNum)
{
	q.push(nStartVtxNum);
	arrIsVisit[nStartVtxNum] = 1;

	while (q.empty()==false)
	{
		int temp = q.front();
		q.pop();

		printf("%d ", temp);

		//인접 정점을 찾아서 큐에 Push
		int row = temp;
		for (int col = 1; col <= nTotVertex; col++)
		{
			if (arrVtxMat[row][col] == 1 && arrIsVisit[col] == 0)
			{
				q.push(col);
				arrIsVisit[col] = 1;
			}
		}

	}
}
