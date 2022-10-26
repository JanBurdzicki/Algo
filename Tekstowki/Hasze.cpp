#include <bits/stdc++.h>
using namespace std;

// TODO: opis napisac ladniej
// liczba pierwsza, wieksza od dlugosci alfabetu
// czyli jesli male litery alfabetu angielskiego to 31, duze i male to 53, itd
const int p = 31;

// const int MOD = 1e9 + 9; zastanowic sie czy to czy to ponizej
const int MOD = 1e9 + 7;

const int MAX_N = 1e5 + 5;

vector <int> hasze(MAX_N);

long long oblicz_hasz(const string& s)
{
	long long wartosc_hasza = 0;

	long long potega_p = 1;

	// zastanowic sie czy nie lepiej jest od i = 0, do n wtedy mamy indeksy
	// zastanowic sie czy a, c, x
	for(auto& c : s)
	{
		wartosc_hasza = (wartosc_hasza + (c - 'a' + 1) * potega_p) % MOD;

		potega_p = (potega_p * p) % MOD;
	}

	return wartosc_hasza;

	//! Jesli chcielibysmy wiele razy tego uzywac, to nalezy zrobic preprocessing poteg liczby p
	// TODO: zapytac sie Bambusa i marasa czy a *= b, a %= MOD, czy a = (a * b) % MOD;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	cout << oblicz_hasz(s) << "\n";

	return 0;
}
