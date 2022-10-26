#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

// SQRT ->

const int SQRT = 316;
const int DLUGOSC_BLOKU = MAX_N / SQRT + 1;

void podziel_liczby_na_bloki(int n)
{
	for(int i = 0; i < n; i++)
	{
		int numer_bloku = i / DLUGOSC_BLOKU;
	}
}

void policz_wynik_dla_bloku(int indeks, int& wynik)
{
	int do_dodania = 0;

	wynik += do_dodania;
}

void policz_wynik_dla_skrawka(int L, int R, int& wynik)
{
	int do_dodania = 0;

	for(int i = L; i <= R; i++)
	{

	}

	wynik += do_dodania;
}

void update(int v)
{
	v--;

	int numer_bloku = v / DLUGOSC_BLOKU;
}


int query(int L, int R)
{
	L--;
	R--;

	int wynik = 0;

	int numer_bloku_L = L / DLUGOSC_BLOKU;
	int numer_bloku_R = R / DLUGOSC_BLOKU;

	if(numer_bloku_L == numer_bloku_R)
	{
		wynik += policz_wynik_dla_skrawka(L, R);
	}

	else
	{
		int lewy_skrawek_L = L;
		int lewy_skrawek_R = (numer_bloku_L + 1) * DLUGOSC_BLOKU - 1;

		int prawy_skrawek_L = numer_bloku_R * DLUGOSC_BLOKU;
		int prawy_skrawek_R = R;

		for(int i = numer_bloku_L + 1; i <= numer_bloku_R - 1; i++)
		{
			wynik += policz_wynik_dla_bloku(i);
		}

		wynik += policz_wynik_dla_skrawka(lewy_skrawek_L, lewy_skrawek_R);
		wynik += policz_wynik_dla_skrawka(prawy_skrawek_L, prawy_skrawek_R);
	}

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <int> liczby(n + 1);

	for(int i = 1; i <= n; i++)
	{
		cin >> liczby[i];
	}

	podziel_liczby_na_bloki(n);

	int t;
	cin >> t;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int operacja;
		cin >> operacja;

		// update w punkcie
		if(operacja == 0)
		{
			int v;
			cin >> v;

			update(v);
		}

		// query na przedziale
		// if(operacja == 1)
		else
		{
			int L, R;
			cin >> L >> R;

			int wynik = query(L, R);

			cout << wynik << "\n";
		}
	}

	return 0;
}
