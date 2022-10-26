#include <bits/stdc++.h>
using namespace std;

long long powmod(long long podstawa, long long wykladnik, int MOD)
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

bool check_composite(int n, int a, int d, int s)
{
	int x = powmod(a, d, n);

	if(x == 1 || x == n - 1)
	{
		return false;
	}

	for(int r = 1; r < s; r++)
	{
		x = (long long) x * x % n;

		if(x == n - 1)
		{
			return false;
		}
	}

	return true;
}

bool is_prime(int n)
{
	if(n <= 4 || n % 2 == 0 || n % 3 == 0)
	{
		return n == 2 || n == 3;
	}

	for (int i = 5; i * i <= n; i += 6)
	{
		if(n % i == 0 || n % (i + 2) == 0)
		{
			return 0;
		}
	}

	return 1;
}

bool Miller_Rabin(int n)
{
	if(n < 2)
	{
		return false;
	}

	if(n < 1000)
	{
		return is_prime(n);
	}

	int r = 0;
	int d = n - 1;

	while((d & 1) == 0)
	{
		d >>= 1;
		r++;
	}

	// for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) // sprawdzanie long longow
	for(int a : {2, 3, 5, 7})
	{
		if(n == a)
		{
			return true;
		}

		if(check_composite(n, a, d, r))
		{
			return false;
		}
	}

	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for(int i = 0; i < n; i++)
	{
		int liczba;
		cin >> liczba;

		if(Miller_Rabin(liczba))
		{
			cout << "YES\n";
		}

		else
		{
			cout << "NO\n";
		}
	}

	return 0;
}