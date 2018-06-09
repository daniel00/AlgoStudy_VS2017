#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

const int MAXT	 = 20;
const int MAXNUM = 100000;	//작은 샘플만들때
const int MAXQ	 = 300000-10;

int vbackup[MAXNUM+1];

int main()
{
	FILE* f = fopen("sample_input_large.txt", "w");

	int testcnt, q;
	int act;
	int num;
	int numBackup;
	int cnt;

	testcnt = MAXT;
	fprintf(f, "%d\n", testcnt);
	
	while(testcnt--)
	{
		q = rand()% MAXQ +10;		//쿼리개수 10~300000				
		fprintf(f, "%d\n", q);	

		memset(vbackup, 0, sizeof(vbackup));
		cnt = 0;

		for(int i=0; i<q; i++)
		{
			if (i< q/2+1)						//반이상은 무조건 act1
			{
				act = 1;					//번호뽑기
				num = rand() % MAXNUM + 1;	//number : 1~10
				cnt++;
			}
			else if (i == q-1)				//마지막은 무조건 act 2
			{
				act = 2;
				num = rand() % cnt + 1;	//kth는 현재까지 뽑은 숫자의 개수보다 작아야 함
				cnt--;
			}
			else
			{
				if (cnt == 0)
				{
					act = 1;					//번호뽑기
					num = rand() % MAXNUM + 1;	//number : 1~10
					cnt++;
				}
				else
				{
					act = rand() % 2 + 1;		//act 1/2
					if (act == 1)
					{
						num = rand() % MAXNUM + 1;
						cnt++;
					}
					else if (act == 2)
					{
						num = rand() % cnt + 1;	//kth는 현재까지 뽑은 숫자의 개수보다 작아야 함
						cnt--;
					}
				}
				
			}
			fprintf(f, "%d %d\n", act, num);
		}
	}


	return 0;
}