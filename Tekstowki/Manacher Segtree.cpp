#include <bits/stdc++.h>
using namespace std;

const int BASE = 1 << 19;
const int INF = 1e9 + 5;

struct Wierzcholek
{
	int indeks, wartosc;
};

vector <Wierzcholek> segtree(BASE << 1);

// ! Algorytm Manachera - obliczanie promieni palindromow

vector <int> Manacher_palindromy_parzyste(string s)
{
	// '$' i '#' sa znakami specjalnymi

	string x("$");
	x += s;
	x += '#';

	vector <int> R;

	R.push_back(0);

	int i = 1, j = 0;

	while(i <= (int) x.size() - 1)
	{
		while(x[i - j] == x[i + j + 1])
		{
			j++;
		}

		R.push_back(j);

		int k = 1;

		while(R[i - k] != R[i] - k && k <= j)
		{
			R.push_back(min(R[i - k], R[i] - k));

			k++;
		}

		j = max(j - k, 0);
		i += k;
	}

	return R;
}

vector <int> Manacher_palindromy_nieparzyste(string s)
{
	// '$' i '#' sa znakami specjalnymi

	string x("$");
	x += s;
	x += '#';

	vector <int> R;

	R.push_back(0);

	int i = 1, j = 0;

	while(i <= (int) x.size() - 1)
	{
		while(x[i - j - 1] == x[i + j + 1])
		{
			j++;
		}

		R.push_back(j);

		int k = 1;

		while(R[i - k] != R[i] - k && k <= j)
		{
			R.push_back(min(R[i - k], R[i] - k));
			k++;
		}

		j = max(j - k, 0);
		i += k;
	}

	return R;
}

// ! Drzewo Przedzialowe

void update(int v, int wartosc)
{
	int punkt = v;

	v += BASE;

	segtree[v] = {punkt, wartosc};

	// dzielimy v przez 2
	v >>= 1;

	while(v)
	{
		// mnozymy razy 2
		int lewy_syn = v << 1;

		// mnozymy razy 2 i dodajemy 1
		int prawy_syn = (v << 1) + 1;

		segtree[v].wartosc = max(segtree[lewy_syn].wartosc, segtree[prawy_syn].wartosc);

		// dzielimy v przez 2
		v >>= 1;
	}
}

int query(int L, int R, int v = 1, int a = 1, int b = BASE)
{
	if(R < a || L > b || segtree[v].wartosc < R)
	{
		return -1;
	}

	if(a == b)
	{
		return segtree[v].indeks;
	}

	int mid = (a + b) / 2;

	// mnozymy razy 2
	int lewy_syn = v << 1;

	// mnozymy razy 2 i dodajemy 1
	int prawy_syn = (v << 1) + 1;

	int wynik_dla_lewego_poddrzewa = query(L, R, lewy_syn, a, mid);

	if(wynik_dla_lewego_poddrzewa != -1)
	{
		return wynik_dla_lewego_poddrzewa;
	}

	else
	{
		int wynik_dla_prawego_poddrzewa = query(L, R, prawy_syn, mid + 1, b);

		return wynik_dla_prawego_poddrzewa;
	}
}

void solve()
{
	string s;
	cin >> s;

	vector <int> palindromy_parzyste = Manacher_palindromy_parzyste(s);

	int rozmiar = (int) s.size();

	int wynik = 0;

	for(int i = 1; i <= rozmiar; i++)
	{
		update(i, i + palindromy_parzyste[i]);
	}

	for(int i = 1; i <= rozmiar; i++)
	{
		int kandydat = query(i - (palindromy_parzyste[i] / 2) + 1, i);

		if(kandydat != -1)
		{
			wynik = max(wynik, 4 * (i - kandydat));
		}
	}

	cout << wynik << "\n";
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	while(t--)
	{
		solve();
	}

	return 0;
}
