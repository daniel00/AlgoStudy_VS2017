//#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define ALL(v) v.begin(), v.end()
#define REP(i, a, b) for(int i = a; i < b; i++)
#define REPD(i, a, b) for(int i = a; i > b; i--)
#define REPLL(i, a, b) for(ll i = a; i < b; i++)
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FORD(i, a, b) for(int i = a; i >= b; i--)
#define FORLL(i, a, b) for(ll i = a; i <= b; i++)
#define INF 2000000001

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
typedef vector<int>::iterator vit;
typedef set<int>::iterator sit;
typedef map<int, int>::iterator mit;
typedef vector<int> vi;
typedef vector<pii > vpii;

#define pb push_back
#define mp make_pair
#define st first
#define nd second

#define EPS 1e-9
#define PI acos(-1.0)
#define MAXN 200007

int z, n, t, ANS, b, c;
int ans[MAXN << 4];
int kroot[MAXN];
int root[MAXN];
int lt[MAXN << 4];
int rt[MAXN << 4];
int next_free;

int nTestCase;
string strTmp;

void build(int v, int l, int r) {
	if (l == r) return;
	lt[v] = next_free++;
	rt[v] = next_free++;
	int mid = (l + r) / 2;
	build(lt[v], l, mid);
	build(rt[v], mid + 1, r);
}

int insert(int v, int x, int l, int r) {
	int nv = next_free++;
	if (l == r) {
		ans[nv] = 1;
		return nv;
	}
	int mid = (l + r) / 2;
	lt[nv] = lt[v];
	rt[nv] = rt[v];
	if (x <= mid) lt[nv] = insert(lt[v], x, l, mid);
	else rt[nv] = insert(rt[v], x, mid + 1, r);
	ans[nv] = ans[lt[nv]] + ans[rt[nv]];
	return nv;
}

int query(int v, int x, int y, int l, int r) {
	if (l >= x && r <= y) {
		return ans[v];
	}
	int mid = (l + r) / 2;
	int ret = 0;
	if (x <= mid) ret += query(lt[v], x, y, l, mid);
	if (y>mid) ret += query(rt[v], x, y, mid + 1, r);
	return ret;
}

vpii v;
int qr;

int main()
{
	freopen("test_input_tall_5.txt", "r", stdin);
	
	scanf("%d", &nTestCase);

	for (int i = 0; i < nTestCase; i++)
	{
		scanf("%d", &n);
		next_free = 1;
		kroot[n] = INF;
		root[n] = next_free++;

		build(1, 1, n);

		FOR(i, 1, n)
		{
			scanf("%d", &t);
			v.pb(mp(t, i));
		}

		sort(ALL(v));
		FORD(i, n - 1, 0)
		{
			kroot[i] = v[i].st;
			root[i] = insert(root[i + 1], v[i].nd, 1, n);
		}

		//query Ã³¸®
		scanf("%d", &qr);
		printf("#%d ", i + 1);
		REP(i, 0, qr)
		{
			scanf("%d %d %d", &ANS, &b, &c);
			int it = lower_bound(kroot, kroot + n + 1, c + 1) - kroot;
			printf("%d ", query(root[it], ANS, b, 1, n));
		}
		printf("\n");
	}
	
	return 0;
}


