/*
영화 수집 풀이
시간 제한
메모리 제한
제출
정답
맞은 사람
정답 비율
1 초 128 MB 1098 370 252 40.256%
문제

상근이는 영화 DVD 수집가이다. 상근이는 그의 DVD 콜렉션을 쌓아 보관한다.
보고 싶은 영화가 있을 때는, DVD의 위치를 찾은 다음 쌓아놓은 콜렉션이 무너지지 않게 조심스럽게 DVD를 뺀다. 영화를 다 본 이후에는 가장 위에 놓는다.
상근이는 DVD가 매우 많기 때문에, 영화의 위치를 찾는데 시간이 너무 오래 걸린다. 각 DVD의 위치는, 찾으려는 DVD의 위에 있는 영화의 개수만 알면 쉽게 구할 수 있다.
각 영화는 DVD 표지에 붙어있는 숫자로 쉽게 구별할 수 있다.
각 영화의 위치를 기록하는 프로그램을 작성하시오. 상근이가 영화를 한 편 볼 때마다 그 DVD의 위에 몇 개의 DVD가 있었는지를 구해야 한다.


입력
첫째 줄에 테스트 케이스의 개수가 주어진다. 테스트 케이스의 개수는 100개를 넘지 않는다.
각 테스트 케이스의 첫째 줄에는 상근이가 가지고 있는 영화의 수 n과 보려고 하는 영화의 수 m이 주어진다. (1 ≤ n, m ≤ 100,000) 둘째 줄에는 보려고 하는 영화의 번호가 순서대로 주어진다.
영화의 번호는 1부터 n까지 이며, 가장 처음에 영화가 쌓여진 순서는 1부터 증가하는 순서이다. 가장 위에 있는 영화의 번호는 1이다.

출력
각 테스트 케이스에 대해서 한 줄에 m개의 정수를 출력해야 한다. i번째 출력하는 수는 i번째로 영화를 볼 때 그 영화의 위에 있었던 DVD의 개수이다.
상근이는 매번 영화를 볼 때마다 본 영화 DVD를 가장 위에 놓는다.
*/

/*
풀이방법
==>책장의 오른쪽부분에서 책을빼서 왼쪽으로 넣는다고 생각하면 좀더 쉽다
(1)주어지는 N+M 크기의(최대2*M) 배열을 만들어서 영화가 있는지 없는지만을 0/1로 표시하여 놓는다.
==> 실제로는 0/1의 개수를 세어서 펜윅트리로 구현되어 누적합이 저장되어 놓는다
초기값은 1~n까지는 영화가 없음을 의미하는 0을 넣어두고, n+1 ~ n+n까지는 1로 간주하여 누적합을 저장하여 놓는다.

(2)책의 위치만을 저장하는 크기n의 배열을 arrPos 하나더 만들고 책의 위치가 변경될 때마다 새로운 위치를 저장해 놓는다.(위치라함은 위 배열의 인덱스가 될 것이다)
(3)책을 빼면 update(이전index, -1);
책을 넣으면 update(새로운index, +1); //새로운 인덱스는 계속 m-- 하면 된다.

입력으로 주어지는 책번호를
treeIndex = arrPos[책번호];
로 구할 수 있고,
getSum(treeIndex);
로 누적합(해당번호 영화의 위에 놓여져있는 영화의 개수)을 구하여 출력하면 된다.
*/


#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

const int MAXN = 100000;

int pos[MAXN +1];
int BIT[2*MAXN+1];	//최대 N의 2배 +1

int T;
int N, M;

void updateTree(int idx, int val)
{
	while (idx <= MAXN)
	{
		BIT[idx] += val;
		idx += (idx&-idx);
	}
}

int getSum(int idx)
{
	int ans = 0;
	while (idx >= 1)
	{
		ans += BIT[idx];
		idx -= (idx&-idx);
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE
	scanf("%d", &T);

	for (int testcase = 0; testcase<T; testcase++)
	{
		memset(BIT, 0, sizeof(BIT));
		memset(pos, 0, sizeof(pos));

		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++)
		{
			updateTree(M + i, 1);		//DVD가 꽂혀있는곳은 1로 표시한다
			pos[i] = M + i;				//현재 DVD의 위치를 저장해 놓는다
		}

		int m;
		int index;
		for (int i = 1; i <= M; i++)
		{
			scanf("%d", &m);
			index = pos[m];						//보려는 DVD의 위치를 얻어온다
			printf("%d ", getSum(index - 1));	//그 DVD위치의 옆에(index-1) 몇개의 DVD가 있는지 구한다

			updateTree(index, -1);				//DVD를 뽑았으므로 0으로 만들기 위해 -1로 업데이트해준다
			pos[m] = M + 1 - i;					//DVD의 새로운 위치를 저장한다 pos[DVD번호] = 왼쪽새로운위치;
			
			index = pos[m];						
			updateTree(index, 1);				//새로운 위치에는 DVD가 있음을 표시해준다
		}
		printf("\n");
	}
	return 0;
}