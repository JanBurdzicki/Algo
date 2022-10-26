#include <bits/stdc++.h>
using namespace std;

const int BASE = 1 << 17;

vector <long long> segtree(BASE << 1);

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
	long long wynik = 0;

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
