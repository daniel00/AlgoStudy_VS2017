#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <functional>

using namespace std;

const int N = 3e5 + 5;
typedef pair <int, int> ii;
int t[20][N], a[N];
ii p[N];

void bulid_tree(int node, int start, int end) 
{

	if (start > end) return;

	for (int i = start; i <= end; i++)
		t[node][i] = t[node - 1][i];

	if (start < end) 
	{
		int m = (start + end) / 2;
		bulid_tree(node + 1, start, m);
		bulid_tree(node + 1, m + 1, end);
		int i = start, j = m + 1;

		int tp = start;
		while (i <= m || j <= end) {
			if (i <= m && (j > end || (j <= end && t[node + 1][i] <= t[node + 1][j])))
				t[node][tp++] = t[node + 1][i++];
			else
				t[node][tp++] = t[node + 1][j++];
		}
	}
}

int get(int d, int l, int r, int x, int y, int k) 
{
	if (l == r) 
		return l;
	else 
	{
		int m = (l + r) >> 1;
		int c = upper_bound(t[d + 1] + l, t[d + 1] + m + 1, y) - lower_bound(t[d + 1] + l, t[d + 1] + m + 1, x);

		if (k <= c) 
			return get(d + 1, l, m, x, y, k);
		else 
			return get(d + 1, m + 1, r, x, y, k - c);
	}
	return 0;
}


int main() 
{
	int startTime = clock();

	int nTestCase;
	char* buff;
	freopen("test_input_tall_8.txt", "r", stdin);

	scanf("%d", &nTestCase);
	for (int testcase = 0; testcase < nTestCase; testcase++)
	{
		memset(t, 0, sizeof(t));
		memset(a, 0, sizeof(a));

		int n, Q;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) 
		{
			scanf("%d", a + i);
			p[i] = ii(a[i], i);			//value, index를 pair배열에 저장
		}
		sort(p + 1, p + n + 1, greater<ii>());

		for (int i = 1; i <= n; i++)
			t[0][i] = p[i].second;		//source 배열의 index를 tree의 node1이 관장하는 배열에 저장, tree는 결국 source 배열의 index를 가지고 있네.

		bulid_tree(1, 1, n);	//node, start, end

		
		
		scanf("%d", &Q);
		
		//print할 buffer 준비
		buff = new char[Q * 10 + 1];				//10 = 9(자리수) +1(" "), 1=null terminated string
		memset(buff, 0, sizeof(char)*Q * 10 + 1);
		int len = 0;

		for (int q = 0; q < Q; q++)
		{
			int l, r, k;
			scanf("%d %d %d", &l, &r, &k);

			//printf("%d ", p[get(1, 1, n, l, r, k)].first);
			len += sprintf(buff+len, "%d ", p[get(1, 1, n, l, r, k)].first);
		}
		printf("#%d %s\n", testcase + 1, buff);
	}
	printf("\nElapsed Time(BIT) : %d ms", clock() - startTime);			//option

}