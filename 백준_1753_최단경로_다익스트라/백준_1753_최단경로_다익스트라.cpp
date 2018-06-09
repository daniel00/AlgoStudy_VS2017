/*
����
����׷����� �־����� �־��� ���������� �ٸ� ��� ���������� �ִ� ��θ� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. ��, ��� ������ ����ġ�� 10 ������ �ڿ����̴�.

�Է�
ù° �ٿ� ������ ���� V�� ������ ���� E�� �־�����. (1��V��20,000, 1��E��300,000) ��� �������� 1���� V���� ��ȣ�� �Ű��� �ִٰ� �����Ѵ�. 
��° �ٿ��� ���� ������ ��ȣ K(1��K��V)�� �־�����. 
��° �ٺ��� E���� �ٿ� ���� �� ������ ��Ÿ���� �� ���� ���� (u, v, w)�� ������� �־�����. �̴� u���� v�� ���� ����ġ w�� ������ �����Ѵٴ� ���̴�. 
u�� v�� ���� �ٸ��� w�� 10 ������ �ڿ����̴�. ���� �ٸ� �� ���� ���̿� ���� ���� ������ ������ ���� ������ �����Ѵ�.

���
ù° �ٺ��� V���� �ٿ� ����, i��° �ٿ� i�� ���������� �ִ� ����� ��ΰ��� ����Ѵ�. ������ �ڽ��� 0���� ����ϰ�, ��ΰ� �������� �ʴ� ��쿡�� INF�� ����ϸ� �ȴ�.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

const int MAX = 987654321;

vector<vector<pair<int, int>>> src;

int V, E;
int K;
int u, v, w;

void Dijkstra(int startNode)
{
	int s, e, w;	//start,end,weight
	int c;			//cost

	vector<int> dist(V+1, MAX);
	priority_queue<pair<int, int>> pq;

	dist[startNode] = 0;
	pq.push(make_pair(0, startNode));

	while (!pq.empty())
	{
		c = -pq.top().first;
		s = pq.top().second;
		pq.pop();

		if (dist[s] < c)
			continue;

		for (int i = 0; i < src[s].size(); i++)
		{
			e = src[s][i].first;
			w = src[s][i].second;

			if (dist[s] + w < dist[e])
			{
				dist[e] = dist[s] + w;				//update dist[] 
				pq.push(make_pair(-dist[e], e));	//update pq
			}
		}
	}

	for (int i = 1; i <= V; i++)
	{
		if (dist[i] == MAX)
			printf("INF\n");
		else
			printf("%d\n", dist[i]);
	}

}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sample_input.txt", "r", stdin);

#endif // !ONLINE_JUDGE

	scanf("%d %d", &V, &E);
	scanf("%d", &K);

	src.resize(V+1);
	for (int i = 0; i < E; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		src[u].push_back(make_pair(v, w));
	}

	Dijkstra(K);

	return 0;
}