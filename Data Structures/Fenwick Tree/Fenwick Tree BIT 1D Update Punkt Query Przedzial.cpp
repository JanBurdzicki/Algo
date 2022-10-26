#include <bits/stdc++.h>
using namespace std;

// TODO: dodac przedzialy np. [0, ..., x][0, ..., y] += val

template <typename T>
struct Fenwick_Tree
{
	vector <T> BIT;
	int n;

	Fenwick_Tree(int rozmiar)
	{
		this->n = rozmiar;

		BIT.resize(n);
	}

	Fenwick_Tree(vector <T>& liczby) : Fenwick_Tree((int) liczby.size() + 1)
	{
		for(int i = 1; i <= (int) liczby.size(); i++)
		{
			update(i, liczby[i]);
		}
	}

	// Least Significant Bit
	int LSB(int v)
	{
		return v & -v;
	}

	void update(int v, T wartosc)
	{
		for(int i = v; i <= n; i += LSB(i))
		{
			BIT[i] += wartosc;
		}
	}

	T policz_sume_prefiksowa(int v)
	{
		// TODO: sprawdzic co to robi -> chyba wywoluje defaultowy konstruktor
		T wynik {};

		for(int i = v; i >= 1; i -= LSB(i))
		{
			wynik += BIT[i];
		}

		return wynik;
	}

	T query(int L, int R)
	{
		return policz_sume_prefiksowa(R) - policz_sume_prefiksowa(L - 1);
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <int> liczby(n + 1);

	for(int i = 1; i <= n; i++)
	{
		cin >> liczby[i];
	}

	Fenwick_Tree <int> fenwick_tree(liczby);

	return 0;
}