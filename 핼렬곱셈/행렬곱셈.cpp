#include <iostream>
#include <string.h>

using namespace std;

unsigned int N;
unsigned int y, x;					//row/column
unsigned int SizeMat[500+1];
unsigned int MinCost[500+1][500+1];		//곱셈횟수 저장

int main()
{
	memset(MinCost, 0x00, sizeof(MinCost));
	memset(SizeMat, 0x00, sizeof(SizeMat));

	freopen("test_input.txt", "r", stdin);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> y >> x;
		SizeMat[i - 1] = y;
		SizeMat[i] = x;			//곱셈시 중복되는 데이터는 미리 오버라이트 될것이다. (2x3)(3x4) => (2x4) 중복되는 3은 제거됨
	}

	int tmp;

	//행렬을 곱하는 모든 경우의 수에 대하여 확인하여야 한다. N-1가지
	for (int r = 1; r <= N - 1; r++)	
	{
		//
		for (int i = 1; i <= N-r; i++)
		{
			int j = i + r;
			int min = 999999999;

			for (int k = i; k <= j-1; k++)
			{
				tmp = MinCost[i][k] + MinCost[k + 1][j] + SizeMat[i - 1]*SizeMat[k]*SizeMat[j];

				if (tmp < min)
					min = tmp;
			}
			MinCost[i][j] = min;
		}
	}
	

	cout << MinCost[1][N];

	return 0;
}