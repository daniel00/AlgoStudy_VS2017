#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	char name[100];
	printf("�ƺ� �̸��� �Է��ϼ��� : \n");
	scanf("%s", name);
	

	while (strcmp(name, "���ٽ�"))
	{
		printf("Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ��� : \n");
		scanf("%s", name);
	}
	printf("�¾ҽ��ϴ�. ���� ����ؿ�!!!\n");


	return 0;
}