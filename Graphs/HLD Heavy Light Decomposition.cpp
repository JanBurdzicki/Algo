#include <bits/stdc++.h>
using namespace std;

// TODO: zrobic druga implementacje, gdzie to jest structem -> chyba ta sobie wybiore

// TODO: dodac segtree
// TODO: zastanowic sie czy chce miec -1, czy 0 nie wystarczy

const int MAX_N = 1e5 + 5;
const int BASE = 1 << 17;

// TODO: zastanowic sie jeszcze nad ulozeniem tych zmiennych
// TODO: dodac komentarz to rozmiaru BASE i ustawic go dobrze
vector <int> segtree(BASE << 1);

// vector <int> graf[MAX_N];
vector <vector <int>> graf(MAX_N);
vector <int> rodzic(MAX_N, -1);
vector <int> glebokosc(MAX_N);

vector <int> dp_rozmiar_poddrzewa(MAX_N);
vector <int> heavy(MAX_N);
vector <int> head(MAX_N, -1);
vector <int> indeks_segtree(MAX_N);

void update(int v, int wartosc)
{
	v += BASE;

	segtree[v] = wartosc;

	// dzielimy v przez 2
	v >>= 1;

	while(v)
	{
		// mnozymy razy 2
		int lewy_syn = v << 1;

		// mnozymy razy 2 i dodajemy 1
		int prawy_syn = (v << 1) + 1;

		segtree[v] = segtree[lewy_syn] + segtree[prawy_syn];

		// dzielimy v przez 2
		v >>= 1;
	}
}

int query(int L, int R)
{
	int wynik = 0;

	L += BASE - 1;
	R += BASE + 1;

	while(R - L > 1)
	{
		// jesli L jest parzyste
		if(!(L & 1))
		{
			wynik += segtree[L + 1];
		}

		// jesli R jest nieparzyste
		if(R & 1)
		{
			wynik += segtree[R - 1];
		}

		// dzielimy v przez 2
		L >>= 1;
		R >>= 1;
	}

	return wynik;
}

void DFS(int v, int poprzednik)
{
	rodzic[v] = poprzednik;

	glebokosc[v] = glebokosc[poprzednik] + 1;

	dp_rozmiar_poddrzewa[v] = 1;

	int max_rozmiar_poddrzewa = 0;

	for(auto& sasiad : graf[v])
	{
		if(sasiad != poprzednik)
		{
			DFS(sasiad, v);

			dp_rozmiar_poddrzewa[v] += dp_rozmiar_poddrzewa[sasiad];

			if(dp_rozmiar_poddrzewa[sasiad] > max_rozmiar_poddrzewa)
			{
				heavy[v] = sasiad;
			}
		}
	}
}

// make_paths
// TODO: moze to nazwac HLD lub HL_Decompose lub pelna nazwa lub dodac komentarz
void DFS_decompose(int v, int glowa, int& indeks)
{
	head[v] = glowa;

	indeks_segtree[v] = indeks;

	indeks++;

	// TODO: chyba czy nie lekka
	if(heavy[v] != -1)
	{
		DFS_decompose(heavy[v], glowa, indeks);
	}

	for(auto& sasiad : graf[v])
	{
		if(sasiad != rodzic[v] && sasiad != heavy[v])
		{
			DFS_decompose(sasiad, sasiad, indeks);
		}
	}
}

// TODO: nwm czy nie chce zamienic na a i b
int policz_wynik_na_sciezce(int L, int R)
{
	int wynik = 0;

	while(head[L] != head[R])
	{
		if(glebokosc[head[L]] > glebokosc[head[R]])
		{
			swap(L, R);
		}

		// TODO: zastanowic sie nad nazwa

		int aktualna_heavy_sciezka = query(indeks_segtree[head[R]], indeks_segtree[R]);

		wynik = combine(wynik, aktualna_heavy_sciezka);

		R = rodzic[head[R]];
	}

	// TODO: dodać komentarz, że to jest ostatnia krawedz

	if(glebokosc[L] > glebokosc[R])
	{
		swap(L, R);
	}

	// query(indeks_segtree[L] + 1, indeks_segtree[R]) -> bez

	int ostatnia_heavy_sciezka = query(indeks_segtree[L], indeks_segtree[R]);

	wynik = combine(wynik, ostatnia_heavy_sciezka);

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for(int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	DFS(1, 1);

	int indeks = 1;

	DFS_decompose(1, 1, indeks);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		int operacja;
		cin >> operacja;

		if(operacja == 1)
		{
			int v, wartosc;
			cin >> v >> wartosc;

			// int indeks_v = indeks_segtree[v];

			// update(indeks_v, wartosc);
		}

		if(operacja == 2)
		{
			int a, b;
			cin >> a >> b;

			// int L = indeks_segtree[a];
			// int R = indeks_segtree[b];

			// cout << query(L, R) << "\n";
		}
	}

	return 0;
}








#include <bits/stdc++.h>
using namespace std;


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		int operacja, L, R;
		cin >> operacja >> L >> R;

		// przypisanie wartosci
		if(operacja == 1)
		{
			update(R, L);
		}

		// suma na przedziale
		// operacja == 0
		else
		{
			cout << query(L, R) << "\n";
		}
	}

	return 0;
}
