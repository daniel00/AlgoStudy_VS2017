#include <iostream>
#include <string.h>

using namespace std;

int compare_qsort(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int compare_bsearch(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}


int main()
{
	int arr_num[] = { 14, 56, 26, 90, 154, 90, 34, 78, 134, 16, 178, 99, 158 };
	int num_of_elem = sizeof(arr_num) / sizeof(int);
	
	qsort(arr_num, num_of_elem, sizeof(int), compare_qsort);
	printf("after sort : ");
	for (int i = 0; i < num_of_elem; i++)
	{
		printf("%d ", arr_num[i]);
	}
	printf("\n");

	int key = 90;
	int* pResult;

	pResult = (int*)bsearch(&key, arr_num, num_of_elem, sizeof(int), compare_bsearch );

	if (pResult == NULL)
		printf("%d 를 찾을 수 없습니다.", key);
	else
		printf("%d 는 배열인덱스 %d번째에 있습니다(arr_num[%d])\n", key, pResult - arr_num,  pResult - arr_num);

	system("pause");

	return 0;
}