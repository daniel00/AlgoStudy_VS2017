#include <iostream>

using namespace std;

int cip[5+1][4+1];	//i열에 패턴P로 놓일 경우의 누적 최대값
int wip[5+1][4+1];	//i열에 패턴P로 놓일 경우의 열의 합	

int S[3+1][5+1];


int GetSum(int col, int nPattern)
{
	int sum = 0;

	switch (nPattern)
	{
	case 1:
		sum = S[1][col];
		break;
	case 2:
		sum = S[2][col];
		break;
	case 3:
		sum = S[3][col];
		break;
	case 4:
		sum = S[1][col] + S[3][col];
	default:
		break;
	}

	return sum;
}

int main()
{
	freopen("test_input.txt", "r", stdin);

	//read array
	for (int row = 1; row <= 5; row++)
		for (int col = 1; col <= 5; col++)
			cin >> S[row][col];

	for (int p = 1; p <= 4; p++)
	{
		cip[1][p] = wip[1][p] = GetSum(1, p);
	}

	return 0;
}
