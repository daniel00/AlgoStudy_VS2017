#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;


char Xm[1000+1];
char Yn[1000+1];
int LCS[1000+1][1000+1];

int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int main()
{
	memset(Xm, 0x00, sizeof(Xm));
	memset(Yn, 0x00, sizeof(Yn));
	memset(LCS, 0x00, sizeof(LCS));

	
	freopen("test_input.txt", "r", stdin);

	cin >> Xm >> Yn;

	int lenM = strlen(Xm);
	int lenN = strlen(Yn);

	for (int m = 1; m <= lenM; m++)
	{
		for (int n = 1; n <= lenN; n++)
		{
			if (Xm[m-1] == Yn[n-1])					//첫번째 글자부터 비교하므로 -1
				LCS[m][n] = LCS[m - 1][n - 1]+1;	//이전 최장길이 보다 1 크다
			else
				LCS[m][n] =	Max(LCS[m][n - 1], LCS[m - 1][n]);
		}
	}

	cout << LCS[lenM][lenN];
	//printf("%d", LCS[lenM][lenN]);

	return 0;
}