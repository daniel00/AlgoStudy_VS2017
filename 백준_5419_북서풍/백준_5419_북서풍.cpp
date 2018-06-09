/*
https://www.acmicpc.net/problem/5419


오른쪽 끝점부터 왼쪽으로 하나씩 이동하며, y값을 점검한다!!!!!!!!

문제를 요약하면,
x, y좌표로 표현되는 점들이 있는데 다음의 두 가지 조건을 모두 만족할 경우에만 이동이 가능하다.
(1)왼쪽에서 오른쪽 으로만
(2)위에서 아래로만
이동이 가능한 점의 쌍의 개수를 구하여라.



풀이방법을 요약하면,
(1)주어진 점을 x값이 큰값->작은값 순으로 정렬 한 후,
(2)정렬된 점을 처음부터 끝까지 점검하면서(결국 오른쪽끝점부터 점검하는것과 같다), 현재점 이전까지 현재점의 y좌표보다 작거나 같은 y좌표를 가진점이 몇번이나 나왔었는지를 세면된다.

아래 그림에서 오른쪽 끝점인 1번 점부터 순서대로 점검하면,
맨오른쪽 부터 점검하므로 왼쪽에서 오른쪽으로 으로 이동한다는 조건은 자연스럽게 만족되는 상황이고,
따라서, 위에서 아래로의 조건이 만족하는지만 점검하면 된다.
이건 점을 점검하고나서 해당 점의 y좌표를 펜윅트리에 집어넣으면 현재점의 y좌표 보다 작거나 같은 점의 개수를 logN시간이내에 찾아낼수 있다.


x좌표를 기준으로 정렬할때에는 주의 할 점이 있는데, x값은 같고 y값만 틀린 점이 있을수 있으므로
이때에는 y값이 작은 값->큰값 순으로 정렬하여야 한다.
예를들어, (10, 5), (10, 2)  의 두점의 경우(10, 2), (10, 5) 순으로 정렬되어야 한다.
작은값이 먼저 점검되면 다음번 큰값 점검시 이동이 가능한 상태가 되지만, 큰값부터 점검되면 이후 작은값 점검시 이동이 불가함을 생각해보면 된다.
y좌표 5->2의 경우 이동이 가능하지만, 2->5의 경우 이동이 불가하므로 이동가능 회수가 달라지게 된다.


*펜윅트리 구현방법
- 주어지는 좌표의 y 값이 - 10 ^ 9~10 ^ 9으로 매우 크고 더구나 음수값도 나올수 있으므로, 배열에 바로 빈도수를 표시할 수 는 없다.
이를 해결하기 위해서, 값을 배열의 인덱스로 치환해서 처리하도록 한다.
(1)y값만 별도의 배열에 저장한후, 향후 바이너리서치를 위해서 오름차순으로 정렬
(2)바이너리 서치로 원래값이 저장되어있 인덱스를 구한다.
(3)펜윅트리의 위 인덱스에  y출현 빈도수를 update() / query() 한다

*y값 배열 정렬후 중복원소 제거는 수행해도 되고 안해도 된다.
왜냐하면 중복원소가 있더라도 lower_bound()는 항상 맨앞 원소의 위치만 리턴하기 때문이다.
*/


#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
vector<pii> point;
vector<int> yTmp;

int T;
int N;

const int MAXN = 75000;
int BIT[MAXN + 1];

int cmp(pii& a, pii& b)
{
	if (a.first == b.first)
		return a.second < b.second;
	else
		return a.first > b.first;
}

void updateBIT(int pos, int val)
{
	pos++;
	while (pos <= N)
	{
		BIT[pos] += val;
		pos += (pos&-pos);
	}
}

ll getSum(int pos)
{
	pos++;
	ll ans = 0;
	while (pos >= 1)
	{
		ans += BIT[pos];
		pos -= (pos&-pos);
	}
	return ans;
}

int main()
{
	//중복요소 삭제 테스트
	/*int arr[] = { 10,20,20,20,30,30,40,40,50 };
	vector<int> test(arr, arr + 9);
	vector<int>::iterator it = unique(test.begin(), test.end());
	test.erase(it, test.end());*/

#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);
#endif
	scanf("%d", &T);
	for (int t = 0; t<T; t++)
	{
		memset(BIT, 0, sizeof(BIT));
		point.clear();
		yTmp.clear();

		scanf("%d", &N);
		int x, y;
		for (int i = 0; i<N; i++)
		{
			scanf("%d %d", &x, &y);
			point.push_back(make_pair(x, y));
			yTmp.push_back(y);											//y값만 별도로 저장한다
		}

		sort(point.begin(), point.end(), cmp);                          //좌표를 x값이 큰것부터 정렬한다

		sort(yTmp.begin(), yTmp.end());                                 //아래에서 바이너리서치를 위해 정렬
	    //yTmp.erase(unique(yTmp.begin(), yTmp.end()), yTmp.end());     //중복원소제거. 수행하지 않아도 된다.

		ll count = 0;
		int yidx;
		for (int i = 0; i<N; i++)
		{

			int yidx = lower_bound(yTmp.begin(), yTmp.end(), point[i].second) - yTmp.begin();  //원래값을 검색해서 그 인덱스를 얻어온다.
			count += getSum(yidx);                                                             //펜윅트리에서 현재y좌표보다 작은 y좌표의 개수를 얻어온다
			updateBIT(yidx, 1);                                                                //펜윅트리에  현재y좌표의 출현비도를 +1 해준다
		}
		printf("%lld\n", count);
	}

	return 0;
}












