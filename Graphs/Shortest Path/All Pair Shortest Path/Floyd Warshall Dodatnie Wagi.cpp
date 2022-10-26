#include <bits/stdc++.h>
using namespace std;

// TODO: mam do dodania: odzyskiwanie sciezki, wagi jako double, ujemny cykl
// TODO: pozbyc sie jakos tablicy booli, poprawic inicjalizacje

const int INF = 1e9 + 5;

struct Floyd_Warshall_Dodatnie_Wagi
{
	static const int MAX_N = 1e3 + 5;
	static const long long INF = 1e18 + 5;

	// dp[i][j] -> dlugosc najkrotszej sciezki z i do j (jesli sciezka nieistnieje, to dp[i][j] == INF)
	vector <vector <long long>> dp = vector <vector <long long>> (MAX_N, vector <long long> (MAX_N));

	Floyd_Warshall_Dodatnie_Wagi(vector <vector <bool>>& czy_istnieje_krawedz, vector <vector <int>>& wagi_krawedzi, int n)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				dp[i][j] = INF;
			}
		}

		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(i == j)
				{
					dp[i][j] = 0;
				}

				if(czy_istnieje_krawedz[i][j])
				{
					dp[i][j] = min(dp[i][j], (long long) wagi_krawedzi[i][j]);
				}
			}
		}

		for(int k = 1; k <= n; k++)
		{
			for(int i = 1; i <= n; i++)
			{
				for(int j = 1; j <= n; j++)
				{
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
				}
			}
		}
	}

	long long dlugosc_najkrotszej_sciezki(int a, int b)
	{
		long long wynik = dp[a][b];

		return wynik;
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector <vector <bool>> czy_istnieje_krawedz(n + 1, vector <bool> (n + 1));
	vector <vector <int>> wagi_krawedzi(n + 1, vector <int> (n + 1, INF));

	for(int i = 0; i < m; i++)
	{
		int a, b, waga;
		cin >> a >> b >> waga;

		czy_istnieje_krawedz[a][b] = true;
		// czy_istnieje_krawedz[b][a] = true;

		wagi_krawedzi[a][b] = min(wagi_krawedzi[a][b], waga);
		// wagi_krawedzi[b][a] = min(wagi_krawedzi[b][a], waga);
	}

	Floyd_Warshall_Dodatnie_Wagi floyd_warshall(czy_istnieje_krawedz, wagi_krawedzi, n);

	int t;
	cin >> t;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int a, b;
		cin >> a >> b;

		long long wynik = floyd_warshall.dlugosc_najkrotszej_sciezki(a, b);

		if(wynik == Floyd_Warshall_Dodatnie_Wagi::INF)
		{
			cout << "-1\n";
		}

		else
		{
			cout << wynik << "\n";
		}
	}

	return 0;
}
