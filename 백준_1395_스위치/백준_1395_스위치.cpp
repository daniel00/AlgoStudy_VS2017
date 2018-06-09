/*
문제
준규네 집에는 총 N개의 스위치가 있고 이를 편하게 1번부터 N번까지 차례대로 번호를 매겼다. 그리고 준규의 취미는 이 스위치들을 켜고 끄는 것이다.

준규가 하는 스위치를 갖고 노는 일은 크게 두 가지이다.
하나는 A번부터 B번 사이의 스위치 상태를 반전시키는 것이고 ,
다른 하나는 C번부터 D번 사이의 스위치 중 켜져 있는 상태의 스위치의 개수를 세는 것이다.

하지만 준규가 싫증을 느껴 우리가 이 귀찮은 일을 떠맡게 되었고 프로그래밍을 통해 일을 처리하도록 결정하였다.

입력
첫 줄에는 스위치의 개수 N(2 ≤ N ≤ 100,000)과 처리할 일의 개수 M(1 ≤ M ≤ 100,000)이 주어진다.
다음 M개의 줄에 대해 각 줄에 처리할 일에 대한 정보가 담겨진 세 개의 정수 O, Si, Ti가 입력된다.
O가 0이면 Si번 스위치부터 Ti번 스위치까지 스위치 상태를 반전시키는 일이고
1이면 Si번 스위치부터 Ti번 스위치까지 중 켜져 있는 상태의 스위치 개수를 묻는 일이다.
단, 초기에는 모든 스위치의 상태는 꺼져있는 상태로 되어있다.

출력
입력에서 켜진 스위치 개수에 대한 답을 한 줄에 하나씩 출력한다.
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5;
int src[MAXN + 1];
int tree[4 * MAXN + 1];
int lazy[4 * MAXN + 1];

int N, M;
int O, S, T;

void updateLazy(int node, int start, int end)
{
	if (lazy[node] != 0)
	{
		//현재 노드에 lazy 적용
		tree[node] = (end - start + 1) - tree[node];	//lazy가 있으면 스위치를 반전시켜야 함. 결국 현재 꺼져있는 스위치가 켜지게 되니깐 이렇게 구하면 됨.

		//리프노드가 아니면 좌우 서브트리에 lazy 전파
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}

		//반복수행 방지를 위해 lazy를 리셋
		lazy[node] = 0;
	}
}

//반전만 하면 되므로 value를 인자로 사용할 필요는 없다
int updateRange(int node, int start, int end, int uleft, int uright)
{
	//이전에 기록된 lazy가 있는지 점검
	updateLazy(node, start, end);

	//(1)업데이트 영역에 포함되지 않으면 현재 노드값 리턴
	if (uright < start || end < uleft)
		return tree[node];

	//(2)업데이트 영역에 노드가 완전히 포함될 경우 : 대표노드에 대해서만 업데이트를 수행하고 lazy를 좌우서브트리에 표시
	if (uleft <= start && end <= uright)
	{
		tree[node] = (end - start + 1) - tree[node]; //스위치 반전후의 개수 저장
		if (start != end)
		{
			lazy[node * 2]     ^= 1;	//xor==반전
			lazy[node * 2 + 1] ^= 1;
		}
		return tree[node]; //빼먹지 말것! 
	}

	//(3)업데이트 영역이 일부만 겹칠경우 좌우 서브트리 점검
	int mid = (start + end) >> 1;
	return tree[node] = updateRange(node * 2, start, mid, uleft, uright) + updateRange(node * 2 + 1, mid + 1, end, uleft, uright);
}

int getSum(int node, int start, int end, int qleft, int qright)
{
	//이전에 기록된 lazy가 있는지 점검
	updateLazy(node, start, end);

	if (qright < start || end < qleft)
		return 0;

	if (qleft <= start && end <= qright)
		return tree[node];

	int mid = (start + end) >> 1;
	return getSum(node * 2, start, mid, qleft, qright) + getSum(node * 2 + 1, mid + 1, end, qleft, qright);
}

int main()
{
	/*test*/
	/*updateRange(1, 1, 4, 1, 2);
	updateRange(1, 1, 4, 2, 4);
	printf("%d\n", getSum(1, 1, 4, 2, 3));*/

#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif // !ONLINE_JUDGE

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d %d", &O, &S, &T);
		if (O == 0)
			updateRange(1, 1, N, S, T);
		else if (O == 1)
			printf("%d\n", getSum(1, 1, N, S, T));
	}

	return 0;
}

