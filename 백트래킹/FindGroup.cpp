#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#define MAX_SIZE	25+1	//0은 사용안함

int arrMap[MAX_SIZE][MAX_SIZE];
int arrVisited[MAX_SIZE][MAX_SIZE];


void BackTracking(int y, int x, int cnt);

int N;

int main()
{

	freopen("test_input.txt", "r", stdin);

	cin >> N;

	char tmp;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> tmp;
			arrMap[i][j] = tmp;
		}
	}

	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
			BackTracking(row, col, 1);
	}
	
	return 0;
}

void BackTracking(int y, int x, int cnt)
{
	if (arrVisited[y][x] == 1) 
		return;

	arrVisited[y][x] = 1;

	//상
	if (arrMap[y - 1][x] == 1 && y >= 2)			BackTracking(y - 1, x, cnt + 1);

	//하
	if (arrMap[y + 1][x] == 1 && y <= N - 1)		BackTracking(y + 1, x, cnt + 1);

	//좌
	if (arrMap[y][x - 1] == 1 && x >= 2)			BackTracking(y, x - 1, cnt + 1);

	//우
	if (arrMap[y][x + 1] == 1 && x <= N - 1)		BackTracking(y, x + 1, cnt + 1);
}