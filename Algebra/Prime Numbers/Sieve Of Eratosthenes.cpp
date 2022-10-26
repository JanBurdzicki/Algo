#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 5;
const int SQRT = 5e5 + 5;
const int MAX_WARTOSC = 5e8 + 5;
const int INF = 1e9 + 5;

vector <bool> czy_pierwsza(MAX_WARTOSC, true);
vector <int> liczby_pierwsze;

// TODO: ogarnac szybkie sito, poki co z rosnacym numerem jest szybciej, 27s, 17s, 13s

void Sito_Eratostenesa_2()
{
	czy_pierwsza[0] = false;
	czy_pierwsza[1] = false;

	liczby_pierwsze.push_back(2);

	for(int i = 4; i < MAX_WARTOSC; i += 2)
	{
		czy_pierwsza[i] = false;
	}

	for(int i = 3; i < MAX_WARTOSC; i += 2)
	{
		if(czy_pierwsza[i])
		{
			liczby_pierwsze.push_back(i);

			for(int j = i; j < MAX_WARTOSC; j += 2 * i)
			{
				czy_pierwsza[j] = false;
			}
		}
	}
}

void Sito_Eratostenesa()
{
	czy_pierwsza[0] = false;
	czy_pierwsza[1] = false;

	for(int i = 2; i < MAX_WARTOSC; i++)
	{
		if(czy_pierwsza[i])
		{
			liczby_pierwsze.push_back(i);

			for(int j = 2 * i; j < MAX_WARTOSC; j += i)
			{
				czy_pierwsza[j] = false;
			}
		}
	}
}

void Sito_Eratostenesa_3()
{
	czy_pierwsza[0] = false;
	czy_pierwsza[1] = false;

	for(int i = 4; i < MAX_WARTOSC; i += 2)
	{
		czy_pierwsza[i] = false;
	}

	for(int i = 3; i * i < MAX_WARTOSC; i += 2)
	{
		if(czy_pierwsza[i])
		{
			for(int j = i * i; j < MAX_WARTOSC; j += 2 * i)
			{
				czy_pierwsza[j] = false;
			}
		}
	}

	liczby_pierwsze.push_back(2);

	for(int i = 3; i < MAX_WARTOSC; i += 2)
	{
		if(czy_pierwsza[i])
		{
			liczby_pierwsze.push_back(i);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	// Preprocessing generujacy liczby pierwsze

	// Sito_Eratostenesa();
	// Sito_Eratostenesa_2();
	Sito_Eratostenesa_3();

	// for(int i = 0; i < 100; i++)
	for(auto& x : liczby_pierwsze)
	{
		// if
		cout << x << " ";
	}

	cout << "\n";
	return 0;
}