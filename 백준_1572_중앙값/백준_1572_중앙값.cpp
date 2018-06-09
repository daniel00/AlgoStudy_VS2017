#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;
#define MAX_CNT	    (250000)
#define MAX_TREE	(65536)						//Max Tree Index

int N, K;
int gArrSrc[MAX_CNT + 1];
int gArrBIT[MAX_TREE + 1];
ll midVal;

/*
펜윈트리의 특성상 인덱스를1 부터 사용하여야 한다.
근데, 우리는 주어지는 숫자의 빈도수를 펜윅트리에 저장할 건데 입력으로 주어지는 값에 0 이 포함된다.
따라서, 인덱스를 1부터 사용하려면 idx++을 수행해 주어야 한다.
*/
inline void updateBIT(int idx, const int& diffValue)
{
	idx++;
	while (idx <= MAX_TREE)
	{
		gArrBIT[idx] += diffValue;
		idx += (idx&-idx);			//get lowest bit
	}
}

inline ll getSum(int idx)
{
	idx++;
	ll ans = 0;
	while (idx > 0)
	{
		ans += gArrBIT[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

//binary search로 중앙값을 찾는다
inline int GetMidVal()
{
	int C = (K + 1) / 2;
	int s = 0;
	int e = MAX_TREE;
	int m;
	while (s < e)
	{
		m = (s + e) / 2;
		if (getSum(m) < C)
			s = m + 1;
		else
			e = m;
	}
	return s;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !1

	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &gArrSrc[i]);
	}

	//최초 한번은 부분배열의 크기만큼 모든 값을 업데이트 한다
	for (int i = 1; i <= K; i++)
	{
		updateBIT(gArrSrc[i], 1);			//빈도수 테이블 업데이트		
	}
	midVal = GetMidVal();

	//이후 N-K번은 부분배열의 첫 데이터와 끝 데이터만 새로운 값으로 업데이트 한다
	for (int i = 1; i <= N - K; i++)
	{
		updateBIT(gArrSrc[i], -1);			//맨처음 데이터는 제거하고
		updateBIT(gArrSrc[i + K], 1);		//맨끝에 데이터를 추가한다

		midVal += GetMidVal();
	}

	printf("%lld\n", midVal);
	return 0;
}