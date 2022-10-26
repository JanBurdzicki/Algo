#include <bits/stdc++.h>
using namespace std;

// Conquer, laczymy dwie polowki ciagu w calosc tak, zeby elementy byly posortowane rosnaco
void combine(vector <int>& liczby, int L_1, int R_1, int L_2, int R_2)
{
	vector <int> ciag_wynikowy(R_2 - L_1 + 1);

	int wskaznik_na_poczatek_1 = L_1;
	int wskaznik_na_poczatek_2 = L_2;

	int wskaznik_na_ciag_wynikowy = 0;

	while(wskaznik_na_poczatek_1 <= R_1 && wskaznik_na_poczatek_2 <= R_2)
	{
		if(liczby[wskaznik_na_poczatek_1] <= liczby[wskaznik_na_poczatek_2])
		{
			ciag_wynikowy[wskaznik_na_ciag_wynikowy] = liczby[wskaznik_na_poczatek_1];

			wskaznik_na_ciag_wynikowy++;
			wskaznik_na_poczatek_1++;
		}

		else
		{
			ciag_wynikowy[wskaznik_na_ciag_wynikowy] = liczby[wskaznik_na_poczatek_2];

			wskaznik_na_ciag_wynikowy++;
			wskaznik_na_poczatek_2++;
		}
	}

	if(wskaznik_na_poczatek_1 > R_1)
	{
		while(wskaznik_na_poczatek_2 <= R_2)
		{
			ciag_wynikowy[wskaznik_na_ciag_wynikowy] = liczby[wskaznik_na_poczatek_2];

			wskaznik_na_ciag_wynikowy++;
			wskaznik_na_poczatek_2++;
		}
	}

	if(wskaznik_na_poczatek_2 > R_2)
	{
		while(wskaznik_na_poczatek_1 <= R_1)
		{
			ciag_wynikowy[wskaznik_na_ciag_wynikowy] = liczby[wskaznik_na_poczatek_1];

			wskaznik_na_ciag_wynikowy++;
			wskaznik_na_poczatek_1++;
		}
	}

	wskaznik_na_ciag_wynikowy = 0;

	for(int i = L_1; i <= R_2; i++)
	{
		liczby[i] = ciag_wynikowy[wskaznik_na_ciag_wynikowy];

		wskaznik_na_ciag_wynikowy++;
	}
}

// Divide, dzielimy ciag liczb rekurencyjnie na polowki ciagu
void merge_sort(vector <int>& liczby, int L, int R)
{
	int mid = (L + R) / 2;

	if(L != R)
	{
		merge_sort(liczby, L, mid);
		merge_sort(liczby, mid + 1, R);

		combine(liczby, L, mid, mid + 1, R);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <int> liczby(n);

	for(int i = 0; i < n; i++)
	{
		cin >> liczby[i];
	}

	merge_sort(liczby, 0, n - 1);

	for(int i = 0; i < n; i++)
	{
		cout << liczby[i] << " ";
	}

	cout << "\n";
	return 0;
}