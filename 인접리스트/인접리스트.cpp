#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 200000;
vector<int> arr[MAXN+1];	//vector 배열

int N, K;			//정점의 수, 간선의 수
int s, t, v;		//시작점/목적지/가중치(start , target, value)

vector<vector<pair<int, int> > > fw;

int main()
{
	freopen("sample_input_large.txt", "r", stdin);
	
	scanf("%d", &N);
	fw.resize(N+1);
	for (int i = 0; i < N; i++)
	{
		//for (int j = 0; j < N; j++)
			fw[i].push_back(make_pair(2, 2));
	}

	//scanf("%d", &K);
	
	/*for (int i = 0; i < K i++)
	{
		scanf("%d %d %d", &s, &t, &v);
		arr[s].push_back(t);
		arr[s].push_back(v);
	}*/

	/*for (int node = 1; node <= N; node++)
	{
		printf("시작 : %d", node);
		for (int j = 0; j < arr[node].size(); j += 2)
		{
			printf("-> 정점 %d/ 값 %d ", arr[node][j], arr[node][j + 1]);
		}
		printf("\n");
	}*/

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &t);
		arr[i].push_back(t);
	}

	FILE* file = fopen("sample_output.txt", "w");

	for (int i = 1; i <= N; i++)
	{
		//printf("start %d", i);
		fprintf(file, "start %d", i);
		for (int j = 0; j < arr[i].size(); j++)
		{
			//printf(" -> %d", arr[i][j]);
			fprintf(file, " -> %d", arr[i][j]);
		}
		//printf("\n");
		fprintf(file, "\n");
	}
	
	return 0;
}