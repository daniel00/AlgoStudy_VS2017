#include <iostream>
#include <string.h>

using namespace std;

unsigned int N;
unsigned int y, x;					//row/column
unsigned int SizeMat[500+1];
unsigned int MinCost[500+1][500+1];		//����Ƚ�� ����

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
		SizeMat[i] = x;			//������ �ߺ��Ǵ� �����ʹ� �̸� ��������Ʈ �ɰ��̴�. (2x3)(3x4) => (2x4) �ߺ��Ǵ� 3�� ���ŵ�
	}

	int tmp;

	//����� ���ϴ� ��� ����� ���� ���Ͽ� Ȯ���Ͽ��� �Ѵ�. N-1����
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