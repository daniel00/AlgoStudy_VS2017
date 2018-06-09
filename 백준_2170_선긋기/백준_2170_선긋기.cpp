#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
vector<pii> vPoint;

const int MAXN = 1000000;

int N;


int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDEG

	scanf("%d", &N);
	vPoint.resize(N);

	int start, end;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &vPoint[i].first, &vPoint[i].second);
	}
	sort(vPoint.begin(), vPoint.end());

	for (int i = 0; i < vPoint.size(); i++)
	{
		if (i == 0)
		{
			start = vPoint[i].first;
			end = vPoint[i].second;
		}
		else
		{
			if(vPoint[i].first <= end && vPoint[i].second)

		}
	}
	

	return 0;
}