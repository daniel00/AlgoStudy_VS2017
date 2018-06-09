#include <iostream>
#include <cstdio>
#include <time.h>

using namespace std;

const int maxnum = 20;

int main()
{
	srand(time(NULL));

	int ans = rand() % maxnum + 1;		//1~10
	int num;	//숫자를 담아놓을 그릇

	

	while (1)
	{
		printf("1~%d사이의 수를 입력하세요 : ", maxnum);
		scanf("%d", &num);
		if (num == 3237)
		{
			printf("프로그램을 종료할께요. 안녕~~\n");
			printf("\a");
			break;
		}
		//printf("%d\n", num);

		while (num < 1 || maxnum < num)
		{
			printf("1~%d사이만 다시 입력하세요 : ",maxnum);
			scanf("%d", &num);
		}

		while (1)
		{
			if (num == ans)
			{
				printf("\a");
				printf("축하합니다. 정답입니다!!!\n\n");
				break;
			}
			else if (ans < num)
			{
				printf("찾는수는 %d 보다 작습니다. %d보다 작은수를 입력하세요 : ", num, num);
				scanf("%d", &num);
			}
			else if (ans > num)
			{
				printf("찾는수는 %d 보다 큽니다 %d보다 큰수를 입력하세요 : ", num, num);
				scanf("%d", &num);
			}
		}
		continue;
	}
	
	

	return 0;
}