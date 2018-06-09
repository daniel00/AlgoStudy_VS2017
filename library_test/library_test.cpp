#include <iostream>
#include <string>

#include <queue>
#include <stack>

#include <functional>

using namespace std;

int compare_num(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}



int compare_for_search(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

int main()
{
	//string mystr;
	//int num = 1234;

	////itoa(1234, mystr, 10);
	//mystr = to_string(num);

	//int arr[10];

	//memset(arr, 0x00, sizeof(int)* 10);
	//int strlen = mystr.length();
	//printf("%d\n",strlen);

	//queue
	queue<int> myqueue;
	myqueue.push(1);
	myqueue.push(2);
	myqueue.push(3);
	myqueue.push(4);
	printf("queue\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", myqueue.front());
		myqueue.pop();
	}


	//stack
	stack<int> mystack;
	mystack.push(1);
	mystack.push(2);
	mystack.push(3);
	mystack.push(4);
	printf("stack\n");

	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", mystack.top());
		mystack.pop();
	}


	//quick sort
	int arrNum[] = { 4, 7, 3, 5, 19, 45, 12, 9, 71, 55 };
	int sizearr = sizeof(arrNum) / sizeof(int);

	nth_element(arrNum, arrNum + 3, arrNum + sizearr);
	printf("nth element : %d\n", arrNum[3]);

	printf("before sort : ");
	for (int i = 0; i < sizearr; i++)
		printf("%d ", arrNum[i]);
	printf("\n");

	/*qsort(arrNum, sizearr, sizeof(int), compare_num);
	printf("after sort : ");
	for (int i = 0; i < sizearr; i++)
		printf("%d ", arrNum[i]);*/

	//c++ sort()
	printf("\nc++의 sort()함수 사용\n");
	sort(arrNum, arrNum + sizearr);			//배열의 시작주소, 끝주소를 매개변수로 넘겨주면 끝
	printf("after sort : ");
	for (int i = 0; i < sizearr; i++)
		printf("%d ", arrNum[i]);

	//string array 정렬(단어 정렬)
	vector<string> strarr = { "apple", "banana", "pineapple", "melon" };
	printf("\nafter sort : ");
	sort(strarr.begin(), strarr.end());
	for (int i = 0; i < strarr.size(); i++)
		cout << strarr.at(i) << " ";
	cout << "\n";

	//string 정렬
	string test_str = "greatehuman";
	sort(test_str.begin(), test_str.end());						//오름차순
	sort(test_str.begin(), test_str.end(), greater<char>());	//내림차순, 함수템플릿 사용(greather<char>)
	cout << test_str << "\n";

	//test_str.find("t");

	//bsearch
	/*printf("\nbinary search test\n");
	string str = "abcdefgh";
	const char* buf = str.c_str();

	char* ptr = (char*)bsearch("f", buf, strlen(buf), sizeof(char), compare_for_search);

	printf("a의 위치는 %d 입니다\n", ptr-buf);*/
	
}