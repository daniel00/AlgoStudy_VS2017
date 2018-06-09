#include <stdio.h>
#include <string.h>


void Swap(char& a, char& b)
{
	char t;
	t = a;
	a = b;
	b = t;
}



//���������� �ΰ��� ������ ���µ�,
//�ٱ� ������ 0���� n-1���� ���Եǰ�, �ѹ� �������� �����ʺ��� �ѱ��ھ� ���ĵǰ� �ȴ�.
//���� ������ �񱳸� �����ϰ� �Ǵµ� �ٱ������� �ѹ� �������� ��ȸ���� �ϳ��� �پ��� �ɰ��̴�.
//���� num-i ���� ������ ���ٴ°͸� �����ϸ� �ȴ�.
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

	int nStrlen = strlen(arrStr);		//�� ��Ʈ���� �����ϰ� ���ڼ��� 6 ���� ��Ÿ������ ����

	printf("Before : %s\n", arrStr);
	BubbleSort(arrStr, nStrlen);
	printf("After : %s\n", arrStr);

	return 0;
}


