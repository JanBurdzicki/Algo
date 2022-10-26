#include <bits/stdc++.h>
using namespace std;

// TODO: napisać structa do kompresji, ale takiego fajnego
// TODO: napisac tez kompresje z sort {wartosc, indeks} -> autobus z piekiel bram PREOI, mniejsza pamiec
// TODO: moze nowy indeks zmienic na nowa_wartosc

map <int, int> mapka_kompresja;
map <int, int> orginalne_wartosci;

void skompresuj_dane(vector <int>& liczby)
{
	vector <int> wartosci = liczby;

	sort(wartosci.begin(), wartosci.end());

	int nowy_indeks = 1;

	for(auto& x : wartosci)
	{
		if(mapka_kompresja[x] == 0)
		{
			mapka_kompresja[x] = nowy_indeks;

			orginalne_wartosci[nowy_indeks] = x;

			nowy_indeks++;
		}
	}

	for(auto& x : liczby)
	{
		x = mapka_kompresja[x];
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

	skompresuj_dane(liczby);

	return 0;
}