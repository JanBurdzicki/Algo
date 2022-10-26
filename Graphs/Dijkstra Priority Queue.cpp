#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const long long INF = 1e18 + 5;

struct Krawedz
{
	int sasiad, waga;
};

struct Stan
{
	long long dystans;
	int v;

	bool operator < (const Stan& inny) const
	{
		if(dystans != inny.dystans)
		{
			return dystans > inny.dystans;
		}

		else
		{
			return v > inny.v;
		}
	}
};

vector <Krawedz> graf[MAX_N];
vector <long long> dist(MAX_N, INF);

void Dijkstra(int start)
{
	dist[start] = 0;

	priority_queue <Stan> kolejka_priorytetowa;

	kolejka_priorytetowa.push({dist[start], start});

	while(!kolejka_priorytetowa.empty())
	{
		int v = kolejka_priorytetowa.top().v;
		long long dystans = kolejka_priorytetowa.top().dystans;

		kolejka_priorytetowa.pop();

		if(dystans != dist[v])
		{
			continue;
		}

		for(auto& krawedz : graf[v])
		{
			int sasiad = krawedz.sasiad;
			long long waga = krawedz.waga;

			long long nowy_dystans = dist[v] + waga;

			if(nowy_dystans < dist[sasiad])
			{
				dist[sasiad] = nowy_dystans;

				kolejka_priorytetowa.push({dist[sasiad], sasiad});
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
		int a, b, waga;
		cin >> a >> b >> waga;

		graf[a].push_back({b, waga});
		graf[b].push_back({a, waga});
	}

	Dijkstra(1);

	for(int i = 1; i <= n; i++)
	{
		if(dist[i] == INF)
		{
			cout << "-1 ";
		}

		else
		{
			cout << dist[i] << " ";
		}
	}

	cout << "\n";
	return 0;
}
