#include <stdio.h>
#include <string.h>


void Swap(char& a, char& b)
{
	char t;
	t = a;
	a = b;
	b = t;
}



//버블정렬은 두개의 루프가 도는데,
//바깥 루프는 0부터 n-1까지 돌게되고, 한번 돌때마다 오른쪽부터 한글자씩 정렬되게 된다.
//안쪽 루프는 비교를 수행하게 되는데 바깥루프가 한번 돌때마다 비교회수는 하나씩 줄어들게 될것이다.
//따라서 num-i 까지 루프를 돈다는것만 유의하면 된다.
void BubbleSort(char* ar, int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		for (int k = 1; k < num - i; k++)
		{
			if (ar[k - 1] > ar[k])
				Swap(ar[k - 1], ar[k]);
		}
	}
}

int main()
{
	char arrStr[] = "winapi";

	int nStrlen = strlen(arrStr);		//널 스트링을 제외하고 글자수만 6 으로 나타내짐에 유의

	printf("Before : %s\n", arrStr);
	BubbleSort(arrStr, nStrlen);
	printf("After : %s\n", arrStr);

	return 0;
}


