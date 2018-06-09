#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> llp;

vector<llp> point;
vector<ll> w;	//weight

int N;


int main()
{
	int maxXsize = point[N-1].first - point[0].first;

	for (int xsize = 1; xsize < maxXsize; xsize++)
	{
		for (int i = 0; i < N; i++)
		{
			int xstart		= point[i].first;
			int xend		= point[i + xsize].first;
			int xsizeTmp	= xend - xstart;
		}
	}
	return 0;
}