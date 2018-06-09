/*
������ �������� ���� ������ ���� �Ǵ� ������ ����� ��ǥ�� ã�Ƽ� ������ ������ �ִ��� �����Ѵ�.
(�ֱ��� �Ÿ����� ������ ������ ���ٸ� �ٸ� ���� �������� ���������̴�.)
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int shootPos[100001];
int M, N, L;

//������ X��ǥ�� �������� ���� ����� ����� ��ġ�� ���Ѵ�.
//���̳ʸ� ��ġ�� ã���� �ǰڴ�.
int GetNearestShootPos1(int animX)
{
	int start = 0;
	int end = M;
	int mid = (start + end)>>1;		//������2

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

	//��,�� �� �������� X�� �Ÿ��� ���� ª�� ����� ��ġ�� ����
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
		if (b <= L) //y��ǥ�� L���� ũ�� ������ �ʿ䰡 ����
		{
			if (abs(GetNearestShootPos1(a) - a) + b <= L)
				count++;
		}
	}
	printf("%d\n", count);
	return 0;
}