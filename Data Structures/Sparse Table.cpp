#include <bits/stdc++.h>
using namespace std;

// TODO: trzeba jeszcze dopracowac, ale jest juz fajnie

struct Sparse_Table
{
	static const int MAX_N = 1e5 + 5;

	// LOG >= floor(log2(MAX_N)), poniewaz 2 ^ floor(log2(MAX_N)) jest to max dlugosc, ktora miesci sie w MAX_N
	// MAX_N <= 10^7 -> dobra wartoscia LOG jest 25
	static const int LOG = 16;

	int sparse_table[MAX_N][LOG + 1];

	static vector <int> wartosci_logarytmow;

	static void policz_wartosci_logarytmow()
	{
		wartosci_logarytmow[1] = 0;

		for(int i = 2; i < MAX_N; i++)
		{
			wartosci_logarytmow[i] = wartosci_logarytmow[i / 2] + 1;
		}
	}

	// O(N log N)
	Sparse_Table(vector <int>& liczby, int n)
	{
		// for(int i = 0; i < n; i++)
		for(int i = 1; i <= n; i++)
		{
			// sparse_table[i][0] = combine(sparse_table[i][0], liczby[i]);
			sparse_table[i][0] = liczby[i];
		}

		for(int j = 1; j <= LOG; j++)
		{
			// for(int i = 0; i + (1 << j) <= n; i++)
			for(int i = 1; i + (1 << j) <= n + 1; i++)
			{
				sparse_table[i][j] = combine(sparse_table[i][j - 1], sparse_table[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	// O(log N)
	int query(int L, int R)
	{
		int wynik = 0;

		for(int j = LOG; j >= 0; j--)
		{
			int dlugosc_przedzialu = R - L + 1;

			if((1 << j) <= dlugosc_przedzialu)
			{
				wynik = combine(wynik, sparse_table[L][j]);

				L += (1 << j);
			}
		}

		return wynik;
	}

	// O(1)
	int query_w_czasie_stalym(int L, int R)
	{
		int dlugosc_przedzialu = R - L + 1;

		int max_logarytm = wartosci_logarytmow[dlugosc_przedzialu];

		int wynik = combine(sparse_table[L][max_logarytm], sparse_table[R - (1 << max_logarytm) + 1][max_logarytm]);

		return wynik;
	}

	int combine(const int& L, const int& R)
	{
		int wynik = L + R;

		return wynik;
	}
};

vector <int> Sparse_Table::wartosci_logarytmow = vector <int> (MAX_N);

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	Sparse_Table::policz_wartosci_logarytmow();

	vector <int> liczby(n + 1);

	for(int i = 1; i <= n; i++)
	{
		cin >> liczby[i];
	}

	Sparse_Table sparse_table(liczby, n);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		int L, R;
		cin >> L >> R;

		int wynik = sparse_table.query(L, R);

		cout << wynik << "\n";
	}

	return 0;
}
