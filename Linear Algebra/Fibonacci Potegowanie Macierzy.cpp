#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void multiply(long long f[2][2], long long g[2][2])
{
	long long a = (f[0][0] * g[0][0] + f[0][1] * g[1][0]) % (MOD - 1);
	long long b = (f[0][0] * g[0][1] + f[0][1] * g[1][1]) % (MOD - 1);
	long long c = (f[1][0] * g[0][0] + f[1][1] * g[1][0]) % (MOD - 1);
	long long d = (f[1][0] * g[0][1] + f[1][1] * g[1][1]) % (MOD - 1);

	f[0][0] = a;
	f[0][1] = b;
	f[1][0] = c;
	f[1][1] = d;
}

void power(long long f[2][2], long long n)
{
	long long g[2][2] = {{1, 1}, {1, 0}};

	if(n == 0 || n == 1)
	{
		return;
	}

	power(f, n / 2);
	multiply(f, f);

	if(n % 2 == 1)
	{
		multiply(f, g);
	}
}

long long oblicz_wyraz_ciagu_Fibonacciego(long long n)
{
	long long f[2][2] = {{1, 1}, {1, 0}};

	if(n == 0)
	{
		return 0;
	}

	power(f, n - 1);

	return f[0][0] % (MOD - 1);
}

long long oblicz_wyraz_ciagu_Fibonacciego_2(long long n)
{
	if(n == 0)
	{
		return 0;
	}

	if(n == 1)
	{
		return 1;
	}

	return (oblicz_wyraz_ciagu_Fibonacciego_2(n - 1) + oblicz_wyraz_ciagu_Fibonacciego_2(n - 2)) % MOD;
}

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

	long long A, B, numer_wyrazu_ciagu;
	cin >> A >> B >> numer_wyrazu_ciagu;

	// Nasz ciag mozemy zdefiniowac jako
	// F(0) = A
	// F(1) = B
	// F(n) = F(n + 1) * F(n), dla n >= 2

	// Rozpiszmy kolejne wyrazy ciagu, zeby zaobserwowac jakis schemat, wzor
	// F(0) = A ^ 1
	// F(1) = A ^ 0 * B ^ 1
	// F(2) = A ^ 1 * B ^ 1
	// F(3) = A ^ 1 * B ^ 2
	// F(4) = A ^ 2 * B ^ 3
	// F(5) = A ^ 3 * B ^ 5
	// F(6) = A ^ 5 * B ^ 8
	// F(7) = A ^ 8 * B ^ 13

	// UWAGA!!!
	// Zauwazmy, ze (a * b) % MOD == ((a % MOD) * (b % MOD)) % MOD, a wiec nasze rozwiazanie jest poprawne
	// Zauwazmy, ze z Malego Twierdzenia Fermata mamy a ^ (p - 1) % p == 1
	// Wiec chcemy liczyc wyrazy ciagu Fibonacciego % (MOD - 1) a nie MOD (poniewaz one oznaczaja wykladnik) !!!

	// Zauwazmy, ze nasz ciag mozemy rownowaznie zdefiniowac jako
	// F(0) = A
	// F(n) = A ^ oblicz_wyraz_ciagu_Fibonacciego(n - 1) * B ^ oblicz_wyraz_ciagu_Fibonacciego(n), dla n >= 1

	// Do wyliczenia F(n) skorzystamy z szybkiego potegowania modulo
	// A do wyliczenia oblicz_wyraz_ciagu_Fibonacciego(n) skorzystamy z szybkiego potegowania modulo macierzy (potegowanie macierzy)

	long long czesc_A, czesc_B;

	if(numer_wyrazu_ciagu == 0)
	{
		czesc_A = powmod(A, 1);
		czesc_B = 1;
	}

	else
	{
		czesc_A = powmod(A, oblicz_wyraz_ciagu_Fibonacciego(numer_wyrazu_ciagu - 1));
		czesc_B = powmod(B, oblicz_wyraz_ciagu_Fibonacciego(numer_wyrazu_ciagu));
	}

	long long wynik = czesc_A * czesc_B;

	wynik %= MOD;

	cout << wynik << "\n";
	return 0;
}
