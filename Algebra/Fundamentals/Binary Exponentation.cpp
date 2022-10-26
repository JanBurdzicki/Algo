#include <bits/stdc++.h>
using namespace std;

// TODO: mozna uzupelnic o to co jest w CP Algo, ale potegowanie macierzy zrobic oddzielnie
// Szybkie liczenie Fibo bedzie w Fibo


const int MOD = 1e9 + 7; // 998244353

long long powmod(long long podstawa, long long wykladnik)
{
	long long wynik = 1;
	podstawa %= MOD;

	while(wykladnik)
	{
		if(wykladnik & 1)
		{
			wynik *= podstawa;
			wynik %= MOD;
		}

		wykladnik >>= 1;

		podstawa *= podstawa;
		podstawa %= MOD;
	}

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	return 0;
}