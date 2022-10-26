#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Macierz
{
	int macierz[3][3];

	Macierz()
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				macierz[i][j] = 0;
			}
		}
	}

	int* operator [] (int indeks)
	{
		return macierz[indeks];
	}

	const int* operator [] (int indeks) const
	{
		return macierz[indeks];
	}

	Macierz operator * (const Macierz& inny) const
	{
		Macierz wynik;

		for(int k = 0; k < 3; k++)
		{
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					wynik[i][j] = (wynik[i][j] + 1LL * macierz[i][k] * inny.macierz[k][j]) % MOD;
				}
			}
		}

		return wynik;
	}
};

Macierz szybkie_potegowanie_macierzy(Macierz podstawa, long long wykladnik)
{
	Macierz wynik;

	for(int i = 0; i < 3; i++)
	{
		wynik.macierz[i][i] = 1;
	}

	while(wykladnik)
	{
		if(wykladnik & 1)
		{
			wynik = wynik * podstawa;
		}

		wykladnik >>= 1;

		podstawa = podstawa * podstawa;
	}

	return wynik;
}

void init(Macierz& macierz)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i != j)
			{
				macierz[i][j] = 1;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	Macierz macierz;

	init(macierz);
	//liczbe macierz 1 1 0, 1 0 1, 0 1 1
	//liczbe pot 2 ^ k
	//0 1 0 -> macierz
	// potege 2 razy to 2^-1 -> inwersja
	// p tez chce
	// p/q
	int pot = 2;

	for(int i = 0; i < n; i++)
	{
		long long liczba;
		cin >> liczba;

		macierz = szybkie_potegowanie_macierzy(macierz, liczba);
	}

	if(macierz.macierz[1][1] % 2 == 0)
	{
		cout << macierz.macierz[1][1] / 2 << "/" << (macierz.macierz[1][0] + macierz.macierz[1][1] / 2) % MOD << "\n";
	}

	else
	{
		cout << macierz.macierz[1][1] << "/" << (macierz.macierz[1][0] + macierz.macierz[1][1]) % MOD << "\n";
	}

	return 0;
}

// TODO: dobic