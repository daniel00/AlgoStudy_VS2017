#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	char name[100];
	printf("아빠 이름을 입력하세요 : \n");
	scanf("%s", name);
	

	while (strcmp(name, "유근식"))
	{
		printf("틀렸습니다. 다시 입력하세요 : \n");
		scanf("%s", name);
	}
	printf("맞았습니다. 정말 대단해요!!!\n");


	return 0;
}