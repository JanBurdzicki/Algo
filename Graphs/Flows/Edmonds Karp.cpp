#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e2 + 5;
const int INF = 1e9 + 5;

struct Stan
{
	int v, flow;
};

vector <int> graf[MAX_N];
vector <int> transpozycja_grafu[MAX_N];

int przepustowosc_krawedzi[MAX_N][MAX_N];

vector <int> rodzic(MAX_N);

int BFS(int start, int koniec)
{
	fill(rodzic.begin(), rodzic.end(), -1);

	queue <Stan> kolejka;

	kolejka.push({start, INF});

	rodzic[start] = -2;

	while(!kolejka.empty())
	{
		int v = kolejka.front().v;
		int flow = kolejka.front().flow;

		kolejka.pop();

		for(auto& sasiad : graf[v])
		{
			if(rodzic[sasiad] == -1 && przepustowosc_krawedzi[v][sasiad] > 0)
			{
				rodzic[sasiad] = v;

				int nowe_flow = min(flow, przepustowosc_krawedzi[v][sasiad]);

				if(sasiad == koniec)
				{
					return nowe_flow;
				}

				kolejka.push({sasiad, nowe_flow});
			}
		}
	}

	return 0;
}

int policz_max_flow(int start, int koniec)
{
	int flow = 0;

	int nowe_flow;

	// TODO: zmienic, bo brzydko

	while(nowe_flow = BFS(start, koniec))
	{
		flow += nowe_flow;

		int v = koniec;

		while(v != start)
		{
			int poprzedni = rodzic[v];

			przepustowosc_krawedzi[poprzedni][v] -= nowe_flow;
			przepustowosc_krawedzi[v][poprzedni] += nowe_flow;

			v = poprzedni;
		}
	}

	return flow;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	// Algorytm Edmondsa Karpa jest implementacja metody Forda Fulkersona,
	// Ktora wykorzystuje BFSa do wyszukiwania sciezek rozszerzajacych (sciezek, ktore moga zwiekszyc przeplyw)

	// Zlozonosc jest niezalezna od maksymalnego przeplywu
	// Algorytm dziala w O(ilosc_wierzcholkow * ilosc_krawedzi ^ 2)
	// Przydaje sie bardzo w przypadkach irracjonalnych przepustowosci

	// Intuicyjnie, jesli za kazdym razem, kiedy natrafiamy na sciezke rozszerzajaca,
	// To jedna z krawedzi ulega nasyceniu, a odleglosc od krawedzi do startu (zrodla) bedzie dluzsza,
	// Jesli pojawi sie pozniej po raz kolejny na sciezce rozszerzajacej
	// Z kolei dlugosc sciezek jest ograniczona przez ilosc_krawedzi

	// Musimy miec odwrocone krawedzie skierowane, kiedy szukamy sciezek rozszerzajacych,
	// A wiec tworzymy sobie graf nieskierowany

	// Funkcja maxflow zwraca wartosc maksymalnego przeplywu

	// Podczas trwania algorytmu tablica przepustowosc_krawedzi bedzie przechowywac faktyczny stan pozostalej pojemnosci sieci

	// TODO:
	// Wartosc przeplywu w kazdej krawedzi nie bedzie faktycznie przechowywana,
	// Ale mozemy to zrobic, uzywajac dodatkowej tablicy

	for(int i = 0; i < m; i++)
	{
		int a, b, przepustowosc;
		cin >> a >> b >> przepustowosc;

		graf[a].push_back(b);
		graf[b].push_back(a);

		przepustowosc_krawedzi[a][b] = przepustowosc;
		przepustowosc_krawedzi[b][a] = przepustowosc;
	}

	// TODO: jakie sa startowe i koncowe wierzcholki

	int start, koniec;

	policz_max_flow(start, koniec);

	return 0;
}

