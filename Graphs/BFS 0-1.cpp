#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int INF = 1e9 + 5;

struct Krawedz
{
	int sasiad, waga;
};

vector <Krawedz> graf[MAX_N];
vector <int> dist(MAX_N, INF);

void BFS(int start)
{
	dist[start] = 0;

	deque <int> kolejka;

	kolejka.push_front(start);

	while(!kolejka.empty())
	{
		int wiersz = kolejka.front();

		kolejka.pop_front();

		for(auto& krawedz : graf[wiersz])
		{
			int sasiad = krawedz.sasiad;
			bool waga = krawedz.waga;

			if(dist[wiersz] + waga < dist[sasiad])
			{
				dist[sasiad] = dist[wiersz] + waga;

				if(waga)
				{
					kolejka.push_back(sasiad);
				}

				else
				{
					kolejka.push_front(sasiad);
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m, start, koniec;
	cin >> n >> m >> start >> koniec;

	// 0 - 1 BFS, szybsza odmiana Dijkstry dla grafow z wagami == {0, 1}
	// O(V + E)

	// To obliczenia najkrotszej sciezki mozemy wykorzystac algorytm Dijkstry
	// Zlozonosc czasowa: O(E + V log V) => O(n + n log n)
	// Mozemy jeszcze szybciej to zrobic, uzywajac 0 - 1 BFS
	// Zlozonosc czasowa: O(V + E) => O(n + n) => O(n)

	// TODO: zastanowic sie czy nie chce miec inta jako wage, bo to chodzi o 2 wartosci a nie dokladnie 0/1

	// Dodajemy krawedzie z waga 0
	// Dodajemy krawedzie z waga 1

	for(int i = 0; i < m; i++)
	{
		int a, b, waga;
		cin >> a >> b >> waga;

		graf[a].push_back({b, waga});
		graf[b].push_back({a, waga});
	}

	BFS(start);

	if(dist[koniec] == INF)
	{
		cout << "-1\n";
	}

	else
	{
		cout << dist[koniec] << "\n";
	}

	return 0;
}