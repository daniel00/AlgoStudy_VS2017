/*******************************************************************************************************
/* 보석가게에 도둑이 들었습니다. 도둑은 최대 W만큼 무게의 보석을 들고 갈 수 있습니다. 무게
가 wi이고 가치가 vi인 보석이 종류별로 한 개씩 있을 때, 도둑이 가져갈 수 있는 보석들의 가
치 합의 최댓값을 구하는 프로그램을 작성하세요.

입력은, 첫줄에 테스트케이스의 개수
두 번째 줄에 보석의 종류 n(1 ≤ n ≤ 100)과 도둑이 들고 갈 수 있는 최대 무게 W(1 ≤ W ≤10000)가 주어집니다. 
세 번째 줄부터 n+1번째 줄까지 보석의 무게 wi(1 ≤ wi ≤ 1000)와 가치vi(1 ≤ vi ≤ 1000)가 순서대로 주어집니다. 
주어지는 입력 값은 모두 자연수입니다.
출력은, 각 테스트케이스에 대해서 보석들의 가치 합의 최댓값을 출력합니다                                                                     */
/********************************************************************************************************/

//풀이
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

#include <algorithm>
#include <functional>
#include <math.h>

using namespace std;

//물건(Y축)-무게(X축) 에 따른 최대가치(이익)가 저장되는 테이블(2차원 배열)을 구하는게 목적이다, 
//반복 계산을 피하고자 저장 후 사용한다.
//계산상 i-1 값이 필요하므로 0을 포함하여 100+1, 10000+1 의 배열크기를 사용한다
int gArrMaxProfit[100+1][10000+1];

int gArrWeight[100+1];
int gArrValue[100+1];

int knapsack_01(int itemcnt, int weightlimit);	//0/1 knapsack 함수

int main()
{
	int nTestCase;
	int nItemCnt;
	int nWeightLimit;

	freopen("test_input.txt", "r", stdin);

	cin >> nTestCase;

	for (int testnum = 0; testnum < nTestCase; testnum++)
	{
		memset(gArrWeight, 0x00, sizeof(int)* 101);
		memset(gArrValue, 0x00, sizeof(int)* 101);
		memset(gArrMaxProfit, 0x00, sizeof(int)* 101 * 10001);

		cin >> nItemCnt >> nWeightLimit;

		for (int i = 1; i <= nItemCnt; i++)
		{
			cin >> gArrWeight[i];
			cin >> gArrValue[i];
		}

		int nMaxVal = knapsack_01(nItemCnt, nWeightLimit);
		printf("%d\n", nMaxVal);
	}
	

	return 0;
}

int knapsack_01(int itemcnt, int weightlimit)
{
	for (int i = 1; i <= itemcnt; i++)
	{
		for (int w = 1; w <= weightlimit; w++)
		{
			if (gArrWeight[i] > w)								//현재 물건의 무게가 w보다 크면 일단 못가져간다.
				gArrMaxProfit[i][w] = gArrMaxProfit[i - 1][w];	//바로 이전 물건의 무게가 w일때의 최대이익을 그대로 사용한다
			else
			{
				int val_if_sel = gArrValue[i] + gArrMaxProfit[i - 1][w - gArrWeight[i]];	//현재물건을 가져갈 경우 : 현재물건의 가치와, 나머지 무게에 대한 이전 물건의 최대가치를 더한다
				int val_if_disel = gArrMaxProfit[i - 1][w];									//가져가지 않을 경우

				gArrMaxProfit[i][w] = max(val_if_sel, val_if_disel);						//이중 더 큰 값을 선택한다
			}
		}
	}

	return gArrMaxProfit[itemcnt][weightlimit];
}