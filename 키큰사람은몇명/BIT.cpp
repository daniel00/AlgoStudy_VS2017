/*
ũ�� N�� �迭��, ���� a, b�� ���ؼ� x���� ū ������ ������ ����϶�
���ѽð� : 2��, �޸�:128MB
�Է�
Test Case
N : �迭�� ũ��(1~300000)
N���� ���Ұ� �������� ���еǾ� �־�����.(������ũ��1~10^9)
Q : ������ ��(1~300000)
���� Q�ٿ� ���ļ� a, b, x 
a,b(1~300000) / x(1~10^9)

ex)
�Է�
1
5
185 196 200 175 195
4
1 3 190
2 4 197
3 5 180
1 5 250

���
#1 2 1 2 0

*/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <string>

typedef long long ll;

using namespace std;

//#define GC getchar_unlocked()
//
//int scan()
//{
//    int ret=0,sign=1;
//    int ip=GC;
//    for(;ip<'0'||ip>'9';ip=GC);
//    for(;ip>='0'&&ip<='9';ip=GC)
//        ret=ret*10+ip-'0';
//    return (ret*sign);
//}


const int N = 300001;
const int Q = 300001;


int BIT[N], ANS[Q];
pair<int, int> source[N];
string strTmp;

struct Query
{
	int idx, s, e, k;	//start/end/k
}query[Q];

bool sort_cond1(const pair<int, int> &q1, const pair<int, int> &q2)
{
	return q1.first > q2.first;
}

bool sort_cond2(const Query &q1, const Query &q2)
{
	return q1.k > q2.k;
}

void update(int idx)
{
	while (idx <= N)
	{
		BIT[idx] += 1;			//�󵵼� ����
		idx += (idx & -idx);
	}
}
int sum(int idx)	//sum
{
	int sum = 0;
	while (idx>0)
	{
		sum += BIT[idx];
		idx -= (idx & -idx);
	}
	return sum;
}
int rangeSum(int l, int r)	//range sum
{
	return sum(r) - sum(l - 1);
}

int main()
{
	//FILE* pFile = fopen("answer_5_file.txt", "w");
	char* buff;

	freopen("test_input_tall_8.txt", "r", stdin);
	
	int startTime = clock();

	int nTestCase;
	scanf("%d", &nTestCase);
	for (int testcase = 0; testcase < nTestCase; testcase++)
	{
		memset(BIT, 0, sizeof(BIT));
		memset(ANS, 0, sizeof(ANS));
		memset(source, 0, sizeof(source));
		memset(query, 0, sizeof(query));

		int n, q;
		int i, j, k;

		//�迭�����͸� �Է¹޴´�
		scanf("%d", &n);
		for (i = 0; i<n; i++)
		{
			scanf("%d", &source[i].first);		//value ����
			source[i].second = i + 1;			//index ����
		}
		//�迭�� value�� �������� �����Ѵ�(ū��--->������)
		sort(source, source + n, sort_cond1);

		//������ �Ѳ����� �Է¹޾� �����Ѵ�
		scanf("%d", &q);
		for (i = 0; i<q; i++)
		{
			scanf("%d %d %d", &query[i].s, &query[i].e, &query[i].k);
			query[i].idx = i;

		}
		//������ k�� �������� �����Ѵ�(ū��--->������)
		sort(query, query + q, sort_cond2);
		
		
		//��������ŭ ������ ���鼭, k���� ū ���� ������ �ִ� "�迭�ε���"�� BIT�� update()�Ѵ�
		//��
		i = 0, j = 0;
		while (i<q)
		{
			k = query[i].k;
			while (j<n && source[j].first > k)	//������ �Ǿ������Ƿ� k������ ū ���� ã�� ȸ���� �پ���.
			{
				update(source[j].second);		//*** BIT�� k���� ū ���� ������ �����Ѵٴ°� ���� �߿��ϴ�!!!!
				j++;
			}

			ANS[query[i].idx] = rangeSum(query[i].s, query[i].e); //s~e���̿��� k���� ū���� ������ ���Ҽ� �ִ�.
			i++;
		}

		/*for (int i = 0; i < q; i++)
		{
			k = query[i].k;
			for (int j = 0; j < n; j++)
			{
				if (source[j].first > k)
					update(source[j].second);
				else
					break;
			}
			ANS[query[i].idx] = rangeSum(query[i].s, query[i].e);
		}*/


		buff = new char[q * 10 + 1];				//10 = 9(�ڸ���) +1(" "), 1=null terminated string
		memset(buff, 0, sizeof(char)*q * 10 + 1);
		int len = 0;

		for (i = 0; i < q; i++)
		{
			//printf("%d ", ANS[i]);					
			len += sprintf(buff+len, "%d ", ANS[i]);
		}
		printf("#%d %s\n",testcase+1, buff);
		//fprintf(pFile, "#%d %s\n", testcase + 1, buff);		//save result to file(option)
		delete[] buff;
	}

	printf("\nElapsed Time(BIT) : %d ms", clock() - startTime);			//option
	//fprintf(pFile, "\nElapsed Time(BIT) : %d ms", clock() - startTime);	//option

	return 0;
}