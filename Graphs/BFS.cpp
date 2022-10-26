#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int INF = 1e9 + 5;

vector <int> graf[MAX_N];
vector <int> dist(MAX_N, INF);

void BFS(int start)
{
	queue <int> kolejka;

	dist[start] = 0;

	kolejka.push(start);

	while(!kolejka.empty())
	{
		int v = kolejka.front();

		kolejka.pop();

		for(auto& sasiad : graf[v])
		{
			int nowy_dystans = dist[v] + 1;

			if(nowy_dystans < dist[sasiad])
			{
				dist[sasiad] = nowy_dystans;

				kolejka.push(sasiad);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	BFS(1);

	for(int i = 1; i <= n; i++)
	{
		cout << dist[i] << " ";
	}

	cout << "\n";
	return 0;
}
