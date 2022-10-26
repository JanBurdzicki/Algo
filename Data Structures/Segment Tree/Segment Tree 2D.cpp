#include <bits/stdc++.h>
using namespace std;

// TODO: naklepac template

const int BASE = 1 << 23;
const int INF = 5e6 + 5;

vector <vector <int>> segtree(BASE << 1);

struct Punkt
{
	int x, y;

	bool operator < (const Punkt& inny) const
	{
		return y < inny.y;
	}
};

vector <int> combine(const vector <int>& L, const vector <int>& R)
{
	vector <int> wierzcholek;

	int wskaznik_1 = 0, wskaznik_2 = 0;

	int rozmiar_1 = (int) L.size();
	int rozmiar_2 = (int) R.size();

	while(wskaznik_1 < rozmiar_1 || wskaznik_2 < rozmiar_2)
	{
		if(wskaznik_1 == rozmiar_1)
		{
			wierzcholek.push_back(R[wskaznik_2]);

			wskaznik_2++;

			continue;
		}

		if(wskaznik_2 == rozmiar_2)
		{
			wierzcholek.push_back(L[wskaznik_1]);

			wskaznik_1++;

			continue;
		}

		if(L[wskaznik_1] < R[wskaznik_2])
		{
			wierzcholek.push_back(L[wskaznik_1]);

			wskaznik_1++;
		}

		else
		{
			wierzcholek.push_back(R[wskaznik_2]);

			wskaznik_2++;
		}
	}

	return wierzcholek;
}

void update(int v, int wartosc)
{
	v += BASE;

	segtree[v].push_back(wartosc);

	// dzielimy v przez 2
	v >>= 1;

	while(v)
	{
		// mnozymy razy 2
		int lewy_syn = v << 1;

		// mnozymy razy 2 i dodajemy 1
		int prawy_syn = (v << 1) + 1;

		segtree[v] = combine(segtree[lewy_syn], segtree[prawy_syn]);

		// dzielimy v przez 2
		v >>= 1;
	}
}

int query(int L_x, int R_x, int L_y, int R_y)
{
	int wynik = 0;

	L_x += BASE - 1;
	R_x += BASE + 1;

	while(R_x - L_x > 1)
	{
		// jesli L jest parzyste
		if(!(L_x & 1))
		{
			wynik += upper_bound(segtree[L_x + 1].begin(), segtree[L_x + 1].end(), R_y) - lower_bound(segtree[L_x + 1].begin(), segtree[L_x + 1].end(), L_y);
		}

		// jesli R jest nieparzyste
		if(R_x & 1)
		{
			wynik += upper_bound(segtree[R_x - 1].begin(), segtree[R_x - 1].end(), R_y) - lower_bound(segtree[R_x - 1].begin(), segtree[R_x - 1].end(), L_y);
		}

		// dzielimy v przez 2
		L_x >>= 1;
		R_x >>= 1;
	}

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, t;
	cin >> n >> t;

	vector <Punkt> punkty(n);

	for(int i = 0; i < n; i++)
	{
		cin >> punkty[i].x >> punkty[i].y;
	}

	sort(punkty.begin(), punkty.end());

	for(int i = 0; i < n; i++)
	{
		update(punkty[i].x, punkty[i].y);
	}

	for(int i = 0; i < t; i++)
	{
		Punkt zapytanie;
		cin >> zapytanie.x >> zapytanie.y;

		cout << query(zapytanie.x, INF, zapytanie.y, INF) << "\n";
	}

	return 0;
}