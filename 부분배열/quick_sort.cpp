#include <iostream>
#include <cstdio>

using namespace std;

void Swap(int& a, int& b)
{
	int tmp;
	tmp = a; a = b; b = tmp;
}

int findKth(int* pArr, int k,int left, int right)
{
	return 0;
}

void quickSort(int* pArr, int sizeArr)
{
	int left, right;
	int key = pArr[sizeArr-1];	//임의로 배열의 마지막 데이터를 기준으로 잡았다

	if (sizeArr <= 1)
		return;

	for (left = 0, right = sizeArr - 2;; left++, right--)
	{
		//배열 좌측에 기준보다 큰 수가 있는지 찾는다
		while (pArr[left] < key) left++;
		while (pArr[right] > key) right--;
		if (right <= left)
			break;
		else
			Swap(pArr[left], pArr[right]);
	}

	Swap(pArr[left], pArr[sizeArr - 1]);	//기준값과 교환

	quickSort(pArr				,left);
	quickSort(pArr + left + 1	,sizeArr - 1 - left);
}

int main()
{
	int arr[] = {10, 4 , 7, 1, 3, 6, 9, 2, 5 };
	int sizeArr = sizeof(arr) / sizeof(int);

	quickSort(arr, sizeArr);

	for (int i = 0; i < sizeArr; i++)
		printf("%d ", arr[i]);

	return 0;
}