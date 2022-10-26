#include <bits/stdc++.h>
using namespace std;

// TODO: dopracowac -> nietestowane, mozliwe bugi, poprawic, rozszerzyc kod

const int BASE = 1 << 20;

struct Wierzcholek
{
	vector <int> wartosci;
};

vector <Wierzcholek> segtree(BASE << 1);

Wierzcholek combine(const Wierzcholek& L, const Wierzcholek& R)
{
	int wskaznik_1 = 0, wskaznik_2 = 0;

	int rozmiar_1 = (int) L.wartosci.size();
	int rozmiar_2 = (int) R.wartosci.size();

	Wierzcholek wierzcholek;

	while(wskaznik_1 < rozmiar_1 || wskaznik_2 < rozmiar_2)
	{
		if(!wierzcholek.wartosci.empty())
		{
			while(wskaznik_1 < rozmiar_1 && L.wartosci[wskaznik_1] == wierzcholek.wartosci.back())
			{
				wskaznik_1++;
			}

			while(wskaznik_2 < rozmiar_2 && R.wartosci[wskaznik_2] == wierzcholek.wartosci.back())
			{
				wskaznik_2++;
			}
		}

		if(wskaznik_1 == rozmiar_1 && wskaznik_2 == rozmiar_2)
		{
			break;
		}

		if(wskaznik_1 == rozmiar_1)
		{
			wierzcholek.wartosci.push_back(R.wartosci[wskaznik_2]);

			wskaznik_2++;

			continue;
		}

		if(wskaznik_2 == rozmiar_2)
		{
			wierzcholek.wartosci.push_back(L.wartosci[wskaznik_1]);

			wskaznik_1++;

			continue;
		}

		if(L.wartosci[wskaznik_1] < R.wartosci[wskaznik_2])
		{
			wierzcholek.wartosci.push_back(L.wartosci[wskaznik_1]);

			wskaznik_1++;
		}

		else
		{
			wierzcholek.wartosci.push_back(R.wartosci[wskaznik_2]);

			wskaznik_2++;
		}
	}

	wierzcholek.wartosci.shrink_to_fit();

	return wierzcholek;
}

void build()
{
	for(int v = BASE - 1; v >= 1; v--)
	{
		// mnozymy razy 2
		int lewy_syn = v << 1;

		// mnozymy razy 2 i dodajemy 1
		int prawy_syn = (v << 1) + 1;

		segtree[v] = combine(segtree[lewy_syn], segtree[prawy_syn]);
	}
}

int query(int L, int R)
{
	Wierzcholek wynik = {};

	L += BASE - 1;
	R += BASE + 1;

	while(R - L > 1)
	{
		// jesli L jest parzyste
		if(!(L & 1))
		{
			wynik = combine(segtree[L + 1], wynik);
		}

		// jesli R jest nieparzyste
		if(R & 1)
		{
			wynik = combine(segtree[R - 1], wynik);
		}

		// dzielimy v przez 2
		L >>= 1;
		R >>= 1;
	}

	return (int) wynik.wartosci.size();
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, t;
	cin >> n >> t;

	vector <int> liczby(n + 1);

	for(int i = 1; i <= n; i++)
	{
		cin >> liczby[i];

		segtree[i + BASE].wartosci.push_back(liczby[i]);
	}

	build();

	// Merge Sort Tree stosujemy glownie w momencie, kiedy musimy odpowiadac na zapytania online

	int poprzedni_wynik = 0;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int wspolczynnik_L, wspolczynnik_R, wspolczynnik_wyniku;
		cin >> wspolczynnik_L >> wspolczynnik_R >> wspolczynnik_wyniku;

		int L = (wspolczynnik_L + poprzedni_wynik * wspolczynnik_wyniku) % n + 1;
		int R = (wspolczynnik_R + poprzedni_wynik * wspolczynnik_wyniku) % n + 1;

		if(L > R)
		{
			swap(L, R);
		}

		int wynik = query(L, R);

		cout << wynik << "\n";

		poprzedni_wynik = wynik;
	}

	return 0;
}
