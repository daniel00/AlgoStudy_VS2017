#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

#include <algorithm>
#include <functional>

using namespace std;

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main()
{
	int arrNum[] = {29, 12, 58, 11, 23, 9, 45, 78};
	int arrsize = sizeof(arrNum) / sizeof(int);

	printf("정렬 전 : ");
	for (int i = 0; i < arrsize; i++)
		printf("%d ", arrNum[i]);
	printf("\n");

	
	sort(arrNum, arrNum + arrsize);		//작은수에서 큰수로 정렬
	//sort(arrNum, arrNum + arrsize, greater<int>()); //큰수에서 작은수로 정렬

	printf("정렬 후 : ");
	for (int i = 0; i < arrsize; i++)
		printf("%d ", arrNum[i]);
	printf("\n");

	
	
	int key = 100;

	//찾는값이 있는지 없는지만을 검색할때
	printf("searching %d ...\n", key);
	bool bFind = binary_search(arrNum, arrNum + arrsize, key);
	if (bFind)
		printf("found!!!\n");
	else
		printf("Not found\n");


	//찾는값의 위치를 알고 싶을때
	int* ptr = (int*)bsearch(&key, arrNum, arrsize, sizeof(int), compare);
	if (ptr == NULL)
		printf("찾는값이 없습니다\n");
	else
		printf("찾는값은 arrNum[%d] 에 있습니다\n", ptr-arrNum);


	return 0;
}