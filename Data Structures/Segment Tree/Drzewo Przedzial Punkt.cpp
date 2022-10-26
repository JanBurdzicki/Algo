#include <bits/stdc++.h>
using namespace std;

const int BASE = 1 << 17;

vector <long long> segtree(BASE << 1);

void update(int L, int R, int wartosc)
{
	L += BASE - 1;
	R += BASE + 1;

	while(R - L > 1)
	{
		// jesli L jest parzyste
		if(!(L & 1))
		{
			segtree[L + 1] += wartosc;
		}

		// jesli R jest nieparzyste
		if(R & 1)
		{
			segtree[R - 1] += wartosc;
		}

		// dzielimy v przez 2
		L >>= 1;
		R >>= 1;
	}
}

int query(int v)
{
	long long wynik = 0;

	v += BASE;

	while(v)
	{
		wynik += segtree[v];

		// dzielimy v przez 2
		v >>= 1;
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
		int operacja;
		cin >> operacja;

		// dodaj na przedziale
		if(operacja == 1)
		{
			int L, R, wartosc;
			cin >> L >> R >> wartosc;

			update(L, R, wartosc);
		}

		// wartosc w punkcie
		// operacja == 0
		else
		{
			int v;
			cin >> v;

			cout << query(v) << "\n";
		}
	}

	return 0;
}