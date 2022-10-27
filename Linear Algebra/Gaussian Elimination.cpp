#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
const double EPSILON = 1e-9;

int Eliminacja_Gaussa(vector <vector <double>>& macierz, vector <int>& odpowiedzi)
{
	int ilosc_wierszy = (int) macierz.size();
	int ilosc_kolumn = (int) macierz[0].size() - 1;

	vector <int> gdzie(ilosc_kolumn, -1);

	int numer_wiersza = 0;
	int numer_kolumny = 0;

	while(numer_wiersza < ilosc_wierszy && numer_kolumny < ilosc_kolumn)
	{
		int wybrany_wiersz = numer_wiersza;

		for(int i = numer_wiersza; i < ilosc_wierszy; i++)
		{
			if(abs(macierz[i][numer_kolumny]) > abs(macierz[wybrany_wiersz][numer_kolumny]))
			{
				wybrany_wiersz = i;
			}
		}

		if(abs(macierz[wybrany_wiersz][numer_kolumny]) < EPSILON)
		{
			numer_kolumny++;

			continue;
		}

		for(int i = numer_kolumny; i <= ilosc_kolumn; i++)
		{
			swap(macierz[wybrany_wiersz][i], macierz[numer_wiersza][i]);
		}

		gdzie[numer_kolumny] = numer_wiersza;

		for(int i = 0; i < ilosc_wierszy; i++)
		{
			if(i != numer_wiersza)
			{
				double wartosc = macierz[i][numer_kolumny] / macierz[numer_wiersza][numer_kolumny];

				for(int j = numer_kolumny; j <= ilosc_kolumn; j++)
				{
					macierz[i][j] -= macierz[numer_wiersza][j] * wartosc;
				}
			}
		}

		numer_wiersza++;
		numer_kolumny++;
	}

	for(int i = 0; i < ilosc_kolumn; i++)
	{
		if(gdzie[i] == -1)
		{
			odpowiedzi[i] = macierz[gdzie[i]][ilosc_kolumn] / macierz[gdzie[i]][i];
		}
	}

	for(int i = 0; i < ilosc_wierszy; i++)
	{
		double suma = 0;

		for(int j = 0; j < ilosc_kolumn; j++)
		{
			suma += odpowiedzi[j] * macierz[i][j];
		}

		if(abs(suma - macierz[i][ilosc_kolumn]) > EPSILON)
		{
			return 0;
		}
	}

	for(int i = 0; i < ilosc_kolumn; i++)
	{
		if(gdzie[i] == -1)
		{
			return INF;
		}
	}

	return 1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);



	return 0;
}


/*

template <class T>
void gaussianElimination(vector<vector<T>> tab, int n, int m) {
	FOR(i, 0, n) {
		FOR(j, i + 1, n) {
			ll a = (1ll * gaus[j][i] * inverse(gaus[i][i])) % MOD;
			FOR(x, i, m) {
				gaus[j][x] -= (1ll * gaus[i][x] * a) % MOD;
				gaus[j][x] = (gaus[j][x] + MOD) % MOD;
			}
		}
	}

	vector<T> c(m - 1);
	for(int i = m - 1; i >= 0; i--) {
		FOR(j, i + 1, m) {
			gaus[i][m] = (1ll * gaus[i][m] + MOD - ((1ll * gaus[i][j] * c[j]) % MOD)) % MOD;
		}
		c[i] = (1ll * gaus[i][m] * inverse(gaus[i][i])) % MOD;
		c[i] = (c[i] + MOD) % MOD;
	}
}


ll inv(ll a, ll n = MOD - 2) {
	ll r = 1;
	while(n) {
		if(n & 1) r = (r * a) % MOD;
		a = (a * a) % MOD;
		n /= 2;
	}
	return r;
}

ll det(vvll gaus) {
	int n = SZ(gaus), m = SZ(gaus[0]);
	ll res = 1;
	FOR(i, 0, n) {
		if(gaus[i][i] == 0) {
			FOR(j, i + 1, n) {
				if(gaus[j][i] != 0) {
					FOR(x, 0, m) swap(gaus[i][x], gaus[j][x]);
					res = MOD - res;
					break;
				}
			}
		}
		FOR(j, i + 1, n) {
			ll a = (gaus[j][i] * inv(gaus[i][i])) % MOD;
			FOR(x, i, m) {
				gaus[j][x] -= (gaus[i][x] * a) % MOD;
				gaus[j][x] = (gaus[j][x] + MOD) % MOD;
			}
		}
	}
	FOR(i, 0, n) res = (res * gaus[i][i]) % MOD;
	res = (res + MOD) % MOD;
	return res;
}

*/