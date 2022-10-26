#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;
const int MOD = 1e9 + 7;

vector <long long> factorial(MAX_N);
vector <long long> inv(MAX_N);
vector <long long> inverse_factorial(MAX_N);

int extended_gcd(int a, int b, long long& x, long long& y)
{
	if(b == 0)
	{
		x = 1;
		y = 0;

		return a;
	}

	long long x1, y1;
	int d = extended_gcd(b, a % b, x1, y1);

	x = y1;
	y = x1 - y1 * (a / b);

	return d;
}

long long C(int liczba, int& ilosc_wystapien_MOD)
{
	long long wynik = 1;

	for(int i = 1; i <= liczba; i++)
	{
		int czynnik = i;

		while(czynnik % MOD == 0)
		{
			czynnik /= MOD;
			ilosc_wystapien_MOD++;
		}

		wynik *= czynnik;
		wynik %= MOD;
	}

	return wynik;
}

int inverse(long long liczba)
{
	long long x, y;

	int g = extended_gcd(liczba, MOD, x, y);

	if(g != 1)
	{
		return 0;
	}

	x = (x % MOD + MOD) % MOD;

	return x;
}

long long policz_C(int n, int k)
{
	if(n < k || k <= 0)
	{
		return 0;
	}

	int ilosc_wystapien_licznik = 0, ilosc_wystapien_mianownik = 0;

	long long wynik = 1;
	wynik *= 1LL * C(n, ilosc_wystapien_licznik);
	wynik %= MOD;
	wynik *= 1LL * inverse(C(k, ilosc_wystapien_mianownik));
	wynik %= MOD;
	wynik *= 1LL * inverse(C(n - k, ilosc_wystapien_mianownik));
	wynik %= MOD;

	if(ilosc_wystapien_licznik > ilosc_wystapien_mianownik)
	{
		wynik = 0;
	}

	return wynik;
}

long long binomial_coefficient(int n, int k)
{
	if(n < k || k <= 0)
	{
		return 0;
	}

	return 1LL * factorial[n] * inverse_factorial[k] % MOD * inverse_factorial[n - k] % MOD;
}

void preprocessing()
{
	factorial[0] = 1;

	for(int i = 1; i < MAX_N; i++)
	{
		factorial[i] = factorial[i - 1] * i % MOD;
	}

	inv[1] = 1;

	for(int i = 2; i < MAX_N; i++)
	{
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
	}

	inverse_factorial[0] = 1;

	for(int i = 1; i < MAX_N; i++)
	{
		inverse_factorial[i] = inverse_factorial[i - 1] * inv[i] % MOD;
	}
}

/*
const int MOD = 1e9 + 7;

// TODO: tutaj jest jakis case, ze mozna obcinac wykladnik jesli MOD jest pierwsze -> z fermata/eulera
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

long long inverse(long long liczba)
{
	return powmod(liczba, MOD - 2);
}
*/

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	return 0;
}