#include <iostream>
#include <cstdio>
#include <time.h>

using namespace std;

const int maxnum = 20;

int main()
{
	srand(time(NULL));

	int ans = rand() % maxnum + 1;		//1~10
	int num;	//���ڸ� ��Ƴ��� �׸�

	

	while (1)
	{
		printf("1~%d������ ���� �Է��ϼ��� : ", maxnum);
		scanf("%d", &num);
		if (num == 3237)
		{
			printf("���α׷��� �����Ҳ���. �ȳ�~~\n");
			printf("\a");
			break;
		}
		//printf("%d\n", num);

		while (num < 1 || maxnum < num)
		{
			printf("1~%d���̸� �ٽ� �Է��ϼ��� : ",maxnum);
			scanf("%d", &num);
		}

		while (1)
		{
			if (num == ans)
			{
				printf("\a");
				printf("�����մϴ�. �����Դϴ�!!!\n\n");
				break;
			}
			else if (ans < num)
			{
				printf("ã�¼��� %d ���� �۽��ϴ�. %d���� �������� �Է��ϼ��� : ", num, num);
				scanf("%d", &num);
			}
			else if (ans > num)
			{
				printf("ã�¼��� %d ���� Ů�ϴ� %d���� ū���� �Է��ϼ��� : ", num, num);
				scanf("%d", &num);
			}
		}
		continue;
	}
	
	

	return 0;
}