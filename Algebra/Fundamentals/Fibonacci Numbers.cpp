#include <bits/stdc++.h>
using namespace std;

// Jesli liczby_Fibonacciego numerujemy od elementu numer 0, to liczby_Fibonacciego[87] = 1100087778366101931 > 1e18
// Czyli liczby_Fibonacciego[87] -> pierwsza liczba Fibonacciego wieksza od 1e18
const int MAX_WYRAZ_CIAGU_FIBONACCIEGO = 87;

vector <long long> liczby_Fibonacciego(MAX_WYRAZ_CIAGU_FIBONACCIEGO + 1);

void preprocessing()
{
	liczby_Fibonacciego[0] = 1;
	liczby_Fibonacciego[1] = 1;

	for(int i = 2; i <= MAX_WYRAZ_CIAGU_FIBONACCIEGO; i++)
	{
		liczby_Fibonacciego[i] = liczby_Fibonacciego[i - 1] + liczby_Fibonacciego[i - 2];
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	// Preprocessing generujacy liczby Fibonacciego

	preprocessing();

	return 0;
}