#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int INF = 1e9 + 5;

vector <int> graf[MAX_N];
vector <int> dist(MAX_N, INF);

void BFS(vector <int>& wierzcholki_startowe)
{
	queue <int> kolejka;

	for(auto& v : wierzcholki_startowe)
	{
		dist[v] = 0;

		kolejka.push(v);
	}

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

	int n, m, ilosc_wierzcholkow_startowych;
	cin >> n >> m >> ilosc_wierzcholkow_startowych;

	vector <int> wierzcholki_startowe(ilosc_wierzcholkow_startowych);

	for(int i = 0; i < ilosc_wierzcholkow_startowych; i++)
	{
		cin >> wierzcholki_startowe[i];
	}

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	BFS(wierzcholki_startowe);

	return 0;
}
