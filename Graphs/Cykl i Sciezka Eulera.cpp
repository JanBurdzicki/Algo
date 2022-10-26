#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 5;
const int MAX_ILOSC_KRAWEDZI = 1e6 + 5;

struct Krawedz
{
	int sasiad, numer_krawedzi;
};

struct Cala_Krawedz
{
	int a, b;

	// TODO: opcjonalnie mozna wage dodac, ale to potem
};

vector <Krawedz> graf[MAX_N];
vector <bool> visited_krawedzie(MAX_ILOSC_KRAWEDZI);

vector <int> obecny_numer_krawedzi(MAX_N);

vector <int> numery_krawedzi_w_cyklu_eulera;

void DFS(int v)
{
	while(obecny_numer_krawedzi[v] < (int) graf[v].size())
	{
		const Krawedz krawedz = graf[v][obecny_numer_krawedzi[v]];

		int numer_krawedzi = krawedz.numer_krawedzi;
		int sasiad = krawedz.sasiad;

		obecny_numer_krawedzi[v]++;

		if(!visited_krawedzie[numer_krawedzi])
		{
			visited_krawedzie[numer_krawedzi] = true;

			DFS(sasiad);

			numery_krawedzi_w_cyklu_eulera.push_back(numer_krawedzi);
		}
	}
}

bool czy_istnieje_sciezka_Eulera()
{

}

bool czy_istnieje_cykl_Eulera()
{

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector <Cala_Krawedz> krawedzie(m);

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		krawedzie[i] = {a, b};

		graf[a].push_back({b, i});
		graf[b].push_back({a, i});
	}

	// TODO: sprawdzenie czy moze istniec cykl Eulera

	czy_istnieje_sciezka_Eulera();
	czy_istnieje_cykl_Eulera();

	bool ok = true;

	for(int i = 1; i <= n; i++)
	{
		int rozmiar = (int) graf[i].size();

		if(rozmiar % 2 == 1)
		{
			ok = false;

			break;
		}
	}

	if(ok)
	{
		for(int i = 1; i <= n; i++)
		{
			// if(!graf[i].empty())
			if(obecny_numer_krawedzi[i] != (int) graf[i].size())
			{
				DFS(i);

				break;
			}
		}

		if((int) numery_krawedzi_w_cyklu_eulera.size() != m)
		{
			ok = false;
		}
	}

	return 0;
}

	// Sciezka Eulera jest sciezka, ktora przechodzi przez wszystkie krawedzie w grafie dokladnie raz,
	// Ale w danym grafie musi istniec dokladnie jedna taka sciezka, czyli nie moze istniec Cykl Eulera
	// (cykl przechodzacy przez wszystkie krawedzie w grafie), poniewaz wtedy moze byc wiele poprawnych odpowiedzi,
	// Dokladniej kazda para tych samych wartosci

	// Twierdzenie o Cyklu Eulera
	// Niepusty graf spojny ma Cykl Eulera wtedy i tylko wtedy, gdy stopien kazdego wierzcholka jest liczba parzysta

	// Twierdzenie o Sciezce Eulera
	// Niepusty graf spojny ma Sciezke Eulera, ale nie ma Cyklu Eulera wtedy i tylko wtedy,
	// Gdy stopien kazdego, oprocz 2 wierzcholkow, jest liczba parzysta
	// Wtedy ta sciezka zaczyna sie w jednym z tych wierzcholkow, a konczy w drugim

	// Z Twierdzenia o Sciezce Eulera otrzymujemy, ze wierzcholek poczatkowy i koncowy Sciezki Eulera,
	// To 2 rozne wierzcholki o stopniu nieparzystym, a pozostale wierzcholki musza byc stopnia parzystego
	// Oraz graf musi byc spojny