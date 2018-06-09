/**
http://fatc.club/2017/03/01/958 에서 공개한 코드
세그먼트 트리에 구간별 배열자체를 정렬하여 저장한다.(merge()함수 사용)

*/



#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb(a) push_back(a)
#define sz(a) ((int)a.size())
#define all(a) a.begin(),a.end()
#define mp(a,b) make_pair((a),(b))
#define ff first
#define ss second

using namespace std;

typedef long long lld;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

const int INF = 987654321;
const long long LINF = 9876543212345;

int N, Q;
int a[100005];
vector<int> s[400005];	//세그먼트 트리는 vector 배열로 구성된다(4*N만큼)
void build(int id = 1, int l = 0, int r = N - 1)
{
	if (l == r) {
		s[id] = vector<int>(1);
		s[id][0] = a[l];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
	
	//좌우자식 배열의 크기만큼(end-start) 배열을 할당 한 후
	//좌우 자식배열을 merge()한다. 이때 merge()함수에서 정렬도 함께 수행된다.
	s[id].resize(r - l + 1, 0);
	merge(s[id << 1].begin(), s[id << 1].end(), s[id << 1 | 1].begin(), s[id << 1 | 1].end(), s[id].begin()); 
}

int query(int x, int y, int k, int id = 1, int l = 0, int r = N - 1)
{
	if (r<x || y<l)
		return 0;

	if (x <= l && r <= y)
		return upper_bound(s[id].begin(), s[id].end(), k) - s[id].begin(); //k보다 작거나 같은 수의 [개수]를 리턴한다.
	
	int mid = (l + r) >> 1;
	return query(x, y, k, id << 1, l, mid) + query(x, y, k, id << 1 | 1, mid + 1, r);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d%d", &N, &Q);
	int i, j, k;
	for (i = 0; i<N; ++i)scanf("%d", &a[i]);
	build();
	for (i = 0; i<Q; ++i) {
		
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		
		//binary search
		//임의의 값(mid)을 변경해가며 mid가 몇번째 숫자인지를 알아낸다(query()의 리턴값이 몇번째 숫자인지 알려준다)
		//즉 임의의 수인 mid가 몇번째 숫자인지 알면 이 값을 C(찾고자하는 k번째 수)와 비교해서 바이너리 서치 영역을 변경해가며 left==right가 될때까지 계속한다.
		//이때 left또는 right가 찾고자 하는 k번째 수가 될 것이다.
		int l = -1000000003;
		int r = 1000000003;
		while (l<r) 
		{
			int mid = (l + r) >> 1;
			if (query(a - 1, b - 1, mid) >= c) 
			{
				r = mid;
			}
			else 
				l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}