/*
https://www.acmicpc.net/problem/5419


������ �������� �������� �ϳ��� �̵��ϸ�, y���� �����Ѵ�!!!!!!!!

������ ����ϸ�,
x, y��ǥ�� ǥ���Ǵ� ������ �ִµ� ������ �� ���� ������ ��� ������ ��쿡�� �̵��� �����ϴ�.
(1)���ʿ��� ������ ���θ�
(2)������ �Ʒ��θ�
�̵��� ������ ���� ���� ������ ���Ͽ���.



Ǯ�̹���� ����ϸ�,
(1)�־��� ���� x���� ū��->������ ������ ���� �� ��,
(2)���ĵ� ���� ó������ ������ �����ϸ鼭(�ᱹ �����ʳ������� �����ϴ°Ͱ� ����), ������ �������� �������� y��ǥ���� �۰ų� ���� y��ǥ�� �������� ����̳� ���Ծ������� ����ȴ�.

�Ʒ� �׸����� ������ ������ 1�� ������ ������� �����ϸ�,
�ǿ����� ���� �����ϹǷ� ���ʿ��� ���������� ���� �̵��Ѵٴ� ������ �ڿ������� �����Ǵ� ��Ȳ�̰�,
����, ������ �Ʒ����� ������ �����ϴ����� �����ϸ� �ȴ�.
�̰� ���� �����ϰ��� �ش� ���� y��ǥ�� ����Ʈ���� ��������� �������� y��ǥ ���� �۰ų� ���� ���� ������ logN�ð��̳��� ã�Ƴ��� �ִ�.


x��ǥ�� �������� �����Ҷ����� ���� �� ���� �ִµ�, x���� ���� y���� Ʋ�� ���� ������ �����Ƿ�
�̶����� y���� ���� ��->ū�� ������ �����Ͽ��� �Ѵ�.
�������, (10, 5), (10, 2)  �� ������ ���(10, 2), (10, 5) ������ ���ĵǾ�� �Ѵ�.
�������� ���� ���˵Ǹ� ������ ū�� ���˽� �̵��� ������ ���°� ������, ū������ ���˵Ǹ� ���� ������ ���˽� �̵��� �Ұ����� �����غ��� �ȴ�.
y��ǥ 5->2�� ��� �̵��� ����������, 2->5�� ��� �̵��� �Ұ��ϹǷ� �̵����� ȸ���� �޶����� �ȴ�.


*����Ʈ�� �������
- �־����� ��ǥ�� y ���� - 10 ^ 9~10 ^ 9���� �ſ� ũ�� ������ �������� ���ü� �����Ƿ�, �迭�� �ٷ� �󵵼��� ǥ���� �� �� ����.
�̸� �ذ��ϱ� ���ؼ�, ���� �迭�� �ε����� ġȯ�ؼ� ó���ϵ��� �Ѵ�.
(1)y���� ������ �迭�� ��������, ���� ���̳ʸ���ġ�� ���ؼ� ������������ ����
(2)���̳ʸ� ��ġ�� �������� ����Ǿ��� �ε����� ���Ѵ�.
(3)����Ʈ���� �� �ε�����  y���� �󵵼��� update() / query() �Ѵ�

*y�� �迭 ������ �ߺ����� ���Ŵ� �����ص� �ǰ� ���ص� �ȴ�.
�ֳ��ϸ� �ߺ����Ұ� �ִ��� lower_bound()�� �׻� �Ǿ� ������ ��ġ�� �����ϱ� �����̴�.
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
	//�ߺ���� ���� �׽�Ʈ
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
			yTmp.push_back(y);											//y���� ������ �����Ѵ�
		}

		sort(point.begin(), point.end(), cmp);                          //��ǥ�� x���� ū�ͺ��� �����Ѵ�

		sort(yTmp.begin(), yTmp.end());                                 //�Ʒ����� ���̳ʸ���ġ�� ���� ����
	    //yTmp.erase(unique(yTmp.begin(), yTmp.end()), yTmp.end());     //�ߺ���������. �������� �ʾƵ� �ȴ�.

		ll count = 0;
		int yidx;
		for (int i = 0; i<N; i++)
		{

			int yidx = lower_bound(yTmp.begin(), yTmp.end(), point[i].second) - yTmp.begin();  //�������� �˻��ؼ� �� �ε����� ���´�.
			count += getSum(yidx);                                                             //����Ʈ������ ����y��ǥ���� ���� y��ǥ�� ������ ���´�
			updateBIT(yidx, 1);                                                                //����Ʈ����  ����y��ǥ�� �����񵵸� +1 ���ش�
		}
		printf("%lld\n", count);
	}

	return 0;
}












