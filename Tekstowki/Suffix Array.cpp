#include <bits/stdc++.h>
using namespace std;

const int DLUGOSC_ALFABETU = 256;

vector <int> posortuj_przesuniecia_cykliczne(const string& s)
{
	int n = (int) s.size();

	vector <int> kubelki(max(DLUGOSC_ALFABETU, n));

	vector <int> indeksy_podslow(n);
	vector <int> grupy_podslow(n);

	for(int i = 0; i < n; i++)
	{
		kubelki[s[i]]++;
	}

	for(int i = 1; i < DLUGOSC_ALFABETU; i++)
	{
		kubelki[i] += kubelki[i - 1];
	}

	for(int i = 0; i < n; i++)
	{
		kubelki[s[i]]--;

		indeksy_podslow[kubelki[s[i]]] = i;
	}

	grupy_podslow[indeksy_podslow[0]] = 0;

	int numer_grupy = 1;

	for(int i = 1; i < n; i++)
	{
		if(s[indeksy_podslow[i]] != s[indeksy_podslow[i - 1]])
		{
			numer_grupy++;
		}

		grupy_podslow[indeksy_podslow[i]] = numer_grupy - 1;
	}

	vector <int> indeksy_podslow_pomocnicze(n);
	vector <int> grupy_podslow_pomocnicze(n);

	for(int h = 0; (1 << h) < n; h++)
	{
		for(int i = 0; i < n; i++)
		{
			indeksy_podslow_pomocnicze[i] = indeksy_podslow[i] - (1 << h);

			if(indeksy_podslow_pomocnicze[i] < 0)
			{
				indeksy_podslow_pomocnicze[i] += n;
			}
		}

		fill(kubelki.begin(), kubelki.begin() + numer_grupy, 0);

		for(int i = 0; i < n; i++)
		{
			kubelki[grupy_podslow[indeksy_podslow_pomocnicze[i]]]++;
		}

		for(int i = 1; i < numer_grupy; i++)
		{
			kubelki[i] += kubelki[i - 1];
		}

		for(int i = n - 1; i >= 0; i--)
		{
			kubelki[grupy_podslow[indeksy_podslow_pomocnicze[i]]]--;

			indeksy_podslow[kubelki[grupy_podslow[indeksy_podslow_pomocnicze[i]]]] = indeksy_podslow_pomocnicze[i];
		}

		grupy_podslow_pomocnicze[indeksy_podslow[0]] = 0;

		numer_grupy = 1;

		for(int i = 1; i < n; i++)
		{
			pair <int, int> obecna_para = {grupy_podslow[indeksy_podslow[i]], grupy_podslow[(indeksy_podslow[i] + (1 << h)) % n]};
			pair <int, int> poprzednia_para = {grupy_podslow[indeksy_podslow[i - 1]], grupy_podslow[(indeksy_podslow[i - 1] + (1 << h)) % n]};

			if(obecna_para != poprzednia_para)
			{
				numer_grupy++;
			}

			grupy_podslow_pomocnicze[indeksy_podslow[i]] = numer_grupy - 1;
		}

		grupy_podslow.swap(grupy_podslow_pomocnicze);
	}

	return indeksy_podslow;
}

vector <int> stworz_tablice_sufiksowa(string s)
{
	s += '$';

	vector <int> posortowane_przesuniecia = posortuj_przesuniecia_cykliczne(s);

	return posortowane_przesuniecia;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	vector <int> tablica_sufiksowa = stworz_tablice_sufiksowa(s);

	for(auto& x : tablica_sufiksowa)
	{
		cout << x << " ";
	}

	cout << "\n";
	return 0;
}
