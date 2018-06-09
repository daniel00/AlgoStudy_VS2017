#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int N = 200000;

	FILE* file = fopen("sample_input_large.txt", "w");
	fprintf(file, "%d\n", N);
	
	for (int i = 2; i <= N; i++)
		fprintf(file, "%d ", i);	//2~200000

	fprintf(file, "%d ", 1);		//1


	return 0;
}