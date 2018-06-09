#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	unsigned int n_1, n_2;
	unsigned long int tmp;
	unsigned long int N;
	int Div = 1000000;

	//freopen("test_input.txt", "r", stdin);

	cin >> N;
	
	n_2 = 0;
	n_1 = 1;

	N = 1000000000000000000;
	//N = 1000;

	for (unsigned long int n = 2; n <= N; n++)
	{
		tmp = (n_2 + n_1)%Div;
		n_2 = n_1;
		n_1 = tmp;
	}

	cout << tmp;

	return 0;
}



//0 1 1 2 3 5