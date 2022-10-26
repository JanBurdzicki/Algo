#include <bits/stdc++.h>
using namespace std;

const int p = 31;
const int MOD = 1e9 + 7;

void Rabin_Karp(const string& wzorzec, const string& tekst, vector <int>& indeksy_wystapien)
{
	int rozmiar_wzorca = (int) wzorzec.size();
	int rozmiar_tekstu = (int) tekst.size();

	int ilosc_poteg_liczby_p = max(rozmiar_wzorca, rozmiar_tekstu);

	vector <long long> potegi_liczby_p(ilosc_poteg_liczby_p);

	potegi_liczby_p[0] = 1;

	for(int i = 1; i < ilosc_poteg_liczby_p; i++)
	{
		potegi_liczby_p[i] = (potegi_liczby_p[i - 1] * p) % MOD;
	}

	vector <long long> hasze_tekstu(rozmiar_tekstu + 1);

	for(int i = 0; i < rozmiar_tekstu; i++)
	{
		hasze_tekstu[i + 1] = (hasze_tekstu[i] + (tekst[i] - 'a' + 1) * potegi_liczby_p[i]) % MOD;
	}

	long long hasz_wzorca = 0;

	for(int i = 0; i < rozmiar_wzorca; i++)
	{
		hasz_wzorca = (hasz_wzorca + (wzorzec[i] - 'a' + 1) * potegi_liczby_p[i]) % MOD;
	}

	for(int i = 0; i + rozmiar_wzorca - 1 < rozmiar_tekstu; i++)
	{
		long long hasz_podslowa = (hasze_tekstu[i + rozmiar_wzorca] - hasze_tekstu[i] + MOD) % MOD;

		if(hasz_podslowa == (hasz_wzorca * potegi_liczby_p[i]) % MOD)
		{
			indeksy_wystapien.push_back(i);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string wzorzec, tekst;
	cin >> wzorzec >> tekst;

	vector <int> indeksy_wystapien;

	Rabin_Karp(wzorzec, tekst, indeksy_wystapien);

	return 0;
}