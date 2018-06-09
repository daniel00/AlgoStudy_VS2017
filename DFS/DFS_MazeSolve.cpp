#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <queue>

typedef struct STRUCT_XY
{
	int x;
	int y;
};

using namespace std;

int nSizeMaze;
char chTmp;

char arrMaze[100 + 1][100 + 1];	//0은 사용하지 않을것이므로 101개 생성
char arrVisit[100 + 1][100 + 1];	//0은 사용하지 않을것이므로 101개 생성

STRUCT_XY stPath;

void DFS(int y, int x, int depth);

int mincnt = 9999999;

int main()
{
	//*********************************************************************
	//read maze file
	freopen("02_test_input_maze.txt","r",stdin);

	cin >> nSizeMaze;

	for (int row = 1; row <= nSizeMaze; row++)
	{
		for (int col = 1; col <= nSizeMaze; col++)
		{
			cin >> chTmp;	//한글자씩 입력받는다
			arrMaze[row][col] = atoi(&chTmp);
		}
	}

	DFS(1,1,1);

	printf("최소블럭수 : %d\n", mincnt);
	//*********************************************************************

	
	return 0;
}

//추가구현 필요내용
//들어갔다가 이동할수 없어서 돌아올 경우 들어갔던 곳을 벽이라고 표시해주는 것도 필요하다.
//이동 경로 출력(입력받은 미로정보에 색깔로 표시해보자, 최단 경로만 다른색깔로 표시해보자)
void DFS(int y, int x, int depth)
{
	arrVisit[y][x] = 1;

	if (y == 5 && x == 5)
	{
		if (mincnt > depth)
			mincnt = depth;

		return;
	}

	arrMaze[y][x] = 0;

	//갈수있는 길이 있는지 판단

	//상
	if (arrMaze[y - 1][x] == 1 && y >= 2)					DFS(y - 1, x, depth+1);

	//하
	if (arrMaze[y + 1][x] == 1 && y <= nSizeMaze - 1)		DFS(y + 1, x, depth + 1);

	//좌
	if (arrMaze[y][x - 1] == 1 && x >= 2)					DFS(y, x - 1, depth + 1);

	//우
	if (arrMaze[y][x + 1] == 1 && x <= nSizeMaze - 1)		DFS(y, x + 1, depth + 1);
}

