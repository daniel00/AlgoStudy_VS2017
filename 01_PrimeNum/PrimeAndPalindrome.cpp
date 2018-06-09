//this string from notebook(master branch)
//commit count++

#include <iostream>
#include <string>
#include "time.h"

using namespace std;

int* arrChkPrime;
void GetPrimeNums(int nNum);
bool IsPrimeNum(int nNum);
bool IsFlipNum(int nNum);

int main()
{

	int nNum;
	int nResultCnt = 0;

	cout << "type number : ";
	cin >> nNum;
	cout << "\n";

	clock_t StartTime = clock();

	arrChkPrime = new int[nNum + 1];	//"0" + 1~nNum
	GetPrimeNums(nNum);

	for (int i = 2; i <= nNum; i++)
	{
		if (IsPrimeNum(i))
		{
			if (IsFlipNum(i))
			{
				printf("%d ", i);   //print prime numbers
				nResultCnt++;
			}
		}
		
	}

	printf("\nResult count : %d\n", nResultCnt);
	printf("\nElapsed time : %.3f sec\n\n", (float)(clock()-StartTime)/1000);

	system("pause"); //remain to open console window 
	return 0;
}



void GetPrimeNums(int nNum)
{
	arrChkPrime[0] = 0;	//mark to not prime
	arrChkPrime[1] = 0;	//mark to not prime

	//mark to prime num for all numbers
	for (int i = 2; i <= nNum; i++)		//skip 0,1
	{
		arrChkPrime[i] = 1;	
	}

	//it is enough to check to sqrt(nNum)
	double dblEndRef = sqrt(nNum);
	
	for (int i = 2; i <= dblEndRef; i++)	
	{
		for (int j = i*i; j <= nNum; j+=i)	//2times:i+i, 3times:i+i+i
		{
			if (arrChkPrime[i] == 0)
				continue;
			else
				arrChkPrime[j] = 0;
		}
	}
}


bool IsPrimeNum(int nNum)
{
	return arrChkPrime[nNum];
}

bool IsFlipNum(int nNum)
{
	bool bIsFlipNum = true;
	
	string str = to_string(nNum);
	int nlen = str.length();

	for (int i = 0; i < nlen/2; i++)
	{
		if (str.at(i) != str.at(nlen - 1 - i))
		{
			bIsFlipNum = false;
			break;
		}
	}

	return bIsFlipNum;
}
