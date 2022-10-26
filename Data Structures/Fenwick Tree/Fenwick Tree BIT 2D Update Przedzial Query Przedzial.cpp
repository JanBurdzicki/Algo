#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e3 + 5;

struct Fenwick_Tree_2D
{
	vector <vector <int>> BIT_2D;
	int n, m;

	Fenwick_Tree_2D(int rozmiar_1, int rozmiar_2)
	{
		this->n = rozmiar_1;
		this->m = rozmiar_2;

		BIT_2D.resize(n, vector <int> (m));
	}

	Fenwick_Tree_2D(vector <vector <int>>& liczby) : Fenwick_Tree_2D((int) liczby.size() + 1, (int) liczby[0].size() + 1)
	{
		for(int i = 1; i <= (int) liczby.size(); i++)
		{
			for(int j = 1; j <= (int) liczby[i].size(); j++)
			{
				update_w_punkcie(i, j, liczby[i][j]);
			}
		}
	}

	// Least Significant Bit
	int LSB(int v)
	{
		return v & -v;
	}

	void update_w_punkcie(int x, int y, int wartosc)
	{
		for(int i = x; i <= n; i += LSB(i))
		{
			for(int j = y; j <= m; j += LSB(j))
			{
				BIT_2D[i][j] += wartosc;
			}
		}
	}

	int policz_sume_prefiksowa(int x, int y)
	{
		int wynik = 0;

		for(int i = x; i >= 1; i -= LSB(i))
		{
			for(int j = y; j >= 1; j -= LSB(j))
			{
				wynik += BIT_2D[i][j];
			}
		}

		return wynik;
	}

	void update(int L_1, int R_1, int L_2, int R_2, int wartosc)
	{
		update_w_punkcie(L_2 + 1, R_2 + 1, wartosc);
		update_w_punkcie(L_1, R_1, wartosc);
		update_w_punkcie(L_1, R_2 + 1, -wartosc);
		update_w_punkcie(L_2, R_1 + 1, -wartosc);
	}

	int query(int L_1, int R_1, int L_2, int R_2)
	{
		return policz_sume_prefiksowa(L_2, R_2) - policz_sume_prefiksowa(L_1 - 1, R_1 - 1);
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector <vector <int>> liczby(n + 1, vector <int> (m + 1));

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			cin >> liczby[i][j];
		}
	}

	Fenwick_Tree_2D fenwick_tree_2D(liczby);

	return 0;
}