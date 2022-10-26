#include <bits/stdc++.h>
using namespace std;

long long algorytm_Hornera(vector <int>& wspolczynniki_wielomianu, int stopien_wielomianu, int punkt)
{
	long long wynik = 0;

	for(int i = stopien_wielomianu; i >= 0; i--)
	{
		wynik *= punkt;
		wynik += wspolczynniki_wielomianu[i];
	}

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, punkt;
	cin >> n >> punkt;

	vector <int> wspolczynniki_wielomianu(n + 1);

	for(int i = 0; i <= n; i++)
	{
		cin >> wspolczynniki_wielomianu[i];
	}

	long long wartosc_wielomianu = algorytm_Hornera(wspolczynniki_wielomianu, n, punkt);

	cout << wartosc_wielomianu << "\n";
	return 0;
}
