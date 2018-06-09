/*
����
�رԳ� ������ �� N���� ����ġ�� �ְ� �̸� ���ϰ� 1������ N������ ���ʴ�� ��ȣ�� �Ű��. �׸��� �ر��� ��̴� �� ����ġ���� �Ѱ� ���� ���̴�.

�ر԰� �ϴ� ����ġ�� ���� ��� ���� ũ�� �� �����̴�.
�ϳ��� A������ B�� ������ ����ġ ���¸� ������Ű�� ���̰� ,
�ٸ� �ϳ��� C������ D�� ������ ����ġ �� ���� �ִ� ������ ����ġ�� ������ ���� ���̴�.

������ �ر԰� ������ ���� �츮�� �� ������ ���� ���ð� �Ǿ��� ���α׷����� ���� ���� ó���ϵ��� �����Ͽ���.

�Է�
ù �ٿ��� ����ġ�� ���� N(2 �� N �� 100,000)�� ó���� ���� ���� M(1 �� M �� 100,000)�� �־�����.
���� M���� �ٿ� ���� �� �ٿ� ó���� �Ͽ� ���� ������ ����� �� ���� ���� O, Si, Ti�� �Էµȴ�.
O�� 0�̸� Si�� ����ġ���� Ti�� ����ġ���� ����ġ ���¸� ������Ű�� ���̰�
1�̸� Si�� ����ġ���� Ti�� ����ġ���� �� ���� �ִ� ������ ����ġ ������ ���� ���̴�.
��, �ʱ⿡�� ��� ����ġ�� ���´� �����ִ� ���·� �Ǿ��ִ�.

���
�Է¿��� ���� ����ġ ������ ���� ���� �� �ٿ� �ϳ��� ����Ѵ�.
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
		//���� ��忡 lazy ����
		tree[node] = (end - start + 1) - tree[node];	//lazy�� ������ ����ġ�� �������Ѿ� ��. �ᱹ ���� �����ִ� ����ġ�� ������ �Ǵϱ� �̷��� ���ϸ� ��.

		//������尡 �ƴϸ� �¿� ����Ʈ���� lazy ����
		if (start != end)
		{
			lazy[node * 2] ^= 1;
			lazy[node * 2 + 1] ^= 1;
		}

		//�ݺ����� ������ ���� lazy�� ����
		lazy[node] = 0;
	}
}

//������ �ϸ� �ǹǷ� value�� ���ڷ� ����� �ʿ�� ����
int updateRange(int node, int start, int end, int uleft, int uright)
{
	//������ ��ϵ� lazy�� �ִ��� ����
	updateLazy(node, start, end);

	//(1)������Ʈ ������ ���Ե��� ������ ���� ��尪 ����
	if (uright < start || end < uleft)
		return tree[node];

	//(2)������Ʈ ������ ��尡 ������ ���Ե� ��� : ��ǥ��忡 ���ؼ��� ������Ʈ�� �����ϰ� lazy�� �¿켭��Ʈ���� ǥ��
	if (uleft <= start && end <= uright)
	{
		tree[node] = (end - start + 1) - tree[node]; //����ġ �������� ���� ����
		if (start != end)
		{
			lazy[node * 2]     ^= 1;	//xor==����
			lazy[node * 2 + 1] ^= 1;
		}
		return tree[node]; //������ ����! 
	}

	//(3)������Ʈ ������ �Ϻθ� ��ĥ��� �¿� ����Ʈ�� ����
	int mid = (start + end) >> 1;
	return tree[node] = updateRange(node * 2, start, mid, uleft, uright) + updateRange(node * 2 + 1, mid + 1, end, uleft, uright);
}

int getSum(int node, int start, int end, int qleft, int qright)
{
	//������ ��ϵ� lazy�� �ִ��� ����
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

