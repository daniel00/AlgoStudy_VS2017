/*
동물을 기준으로 가장 근접한 왼쪽 또는 오른쪽 사대의 좌표를 찾아서 동물을 잡을수 있는지 점검한다.
(최근접 거리에서 동물을 잡을수 없다면 다른 사대는 보나마나 못잡을것이다.)
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int shootPos[100001];
int M, N, L;

//동물의 X좌표를 기준으로 가장 가까운 사대의 위치를 구한다.
//바이너리 서치로 찾으면 되겠다.
int GetNearestShootPos1(int animX)
{
	int start = 0;
	int end = M;
	int mid = (start + end)>>1;		//나누기2

	while (start != mid)
	{
		if (animX == shootPos[mid])
			return shootPos[mid];
		else if (animX < shootPos[mid])
			end = mid;
		else if(animX > shootPos[mid])
			start = mid;

		mid = (start + end) >>1;
	}

	//좌,우 중 동물과의 X축 거리가 좀더 짧은 사대의 위치를 리턴
	if (abs(animX - shootPos[start]) > abs(animX - shootPos[end]))
		return shootPos[end];
	else
		return shootPos[start];
}

//int GetNearestShootPos2(int animX)
//{
//	int left = lower_bound(shootPos, shootPos + M, animX) - shootPos;
//	int right = upper_bound(shootPos, shootPos + M, animX) - shootPos;
//
//	if (left == right)
//	{
//		if (shootPos[left] == animX)
//			return shootPos[left];
//		else
//			return shootPos[left - 1];
//	}
//
//	else if (abs(animX - shootPos[left]) > abs(animX - shootPos[right]))
//		return shootPos[right];
//	else
//		return shootPos[left];
//}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d %d", &M, &N, &L);
	for (int i = 0; i < M; i++)
		scanf("%d", &shootPos[i]);

	sort(shootPos, shootPos + M);

	int a, b;
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a, &b);
		if (b <= L) //y좌표가 L보다 크면 점검할 필요가 없다
		{
			if (abs(GetNearestShootPos1(a) - a) + b <= L)
				count++;
		}
	}
	printf("%d\n", count);
	return 0;
}