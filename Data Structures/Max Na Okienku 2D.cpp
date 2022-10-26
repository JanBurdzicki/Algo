// Jan Burdzicki
#include <bits/stdc++.h>
using namespace std;

vector <int> znajdz_maksimum_na_okienku_1D(vector <int>& liczby, int dlugosc_okienka_na_przedziale)
{
	int n = (int) liczby.size();

	vector <int> wartosci_maksymalne_1D(n - dlugosc_okienka_na_przedziale + 1);

	deque <int> kolejka_monotoniczna;

	for(int i = 0; i < n; i++)
	{
		while(!kolejka_monotoniczna.empty() && liczby[kolejka_monotoniczna.back()] <= liczby[i])
		{
			kolejka_monotoniczna.pop_back();
		}

		kolejka_monotoniczna.push_back(i);

		if(kolejka_monotoniczna.front() <= i - dlugosc_okienka_na_przedziale)
		{
			kolejka_monotoniczna.pop_front();
		}

		if(i + 1 >= dlugosc_okienka_na_przedziale)
		{
			wartosci_maksymalne_1D[i + 1 - dlugosc_okienka_na_przedziale] = liczby[kolejka_monotoniczna.front()];
		}
	}

	return wartosci_maksymalne_1D;
}

vector <vector <int>> znajdz_maksimum_na_okienku_2D(vector <vector <int>>& liczby, int szerokosc_okienka_na_przedziale, int dlugosc_okienka_na_przedziale)
{
	int n = (int) liczby.size();
	int m = (int) liczby[0].size();

	vector < vector <int>> wartosci_maksymalne_w_kolumnie(m - dlugosc_okienka_na_przedziale + 1, vector <int> (n));

	for(int i = 0; i < n; i++)
	{
		vector <int> wartosci_maksymalne_1D = znajdz_maksimum_na_okienku_1D(liczby[i], dlugosc_okienka_na_przedziale);

		for(int j = 0; j < m - dlugosc_okienka_na_przedziale + 1; ++j)
		{
			wartosci_maksymalne_w_kolumnie[j][i] = wartosci_maksymalne_1D[j];
		}
	}

	vector <vector <int>> wartosci_maksymalne_2D(n - szerokosc_okienka_na_przedziale + 1, vector <int> (m - dlugosc_okienka_na_przedziale + 1));

	for(int j = 0; j < m - dlugosc_okienka_na_przedziale + 1; ++j)
	{
		vector <int> wartosci_maksymalne_1D = znajdz_maksimum_na_okienku_1D(wartosci_maksymalne_w_kolumnie[j], szerokosc_okienka_na_przedziale);

		for(int i = 0; i < n - szerokosc_okienka_na_przedziale + 1; ++i)
		{
			wartosci_maksymalne_2D[i][j] = wartosci_maksymalne_1D[i];
		}
	}

	return wartosci_maksymalne_2D;
}

vector <int> znajdz_minimum_na_okienku_1D(vector <int>& liczby, int dlugosc_okienka_na_przedziale)
{
	int n = (int) liczby.size();

	vector <int> wartosci_minimalne_1D(n - dlugosc_okienka_na_przedziale + 1);

	deque <int> kolejka_monotoniczna;

	for(int i = 0; i < n; i++)
	{
		while(!kolejka_monotoniczna.empty() && liczby[kolejka_monotoniczna.back()] >= liczby[i])
		{
			kolejka_monotoniczna.pop_back();
		}

		kolejka_monotoniczna.push_back(i);

		if(kolejka_monotoniczna.front() <= i - dlugosc_okienka_na_przedziale)
		{
			kolejka_monotoniczna.pop_front();
		}

		if(i + 1 >= dlugosc_okienka_na_przedziale)
		{
			wartosci_minimalne_1D[i + 1 - dlugosc_okienka_na_przedziale] = liczby[kolejka_monotoniczna.front()];
		}
	}

	return wartosci_minimalne_1D;
}

vector <vector <int>> znajdz_minimum_na_okienku_2D(vector <vector <int>>& liczby, int szerokosc_okienka_na_przedziale, int dlugosc_okienka_na_przedziale)
{
	int n = (int) liczby.size();
	int m = (int) liczby[0].size();

	vector < vector <int>> wartosci_minimalne_w_kolumnie(m - dlugosc_okienka_na_przedziale + 1, vector <int> (n));

	for(int i = 0; i < n; i++)
	{
		vector <int> wartosci_minimalne_1D = znajdz_minimum_na_okienku_1D(liczby[i], dlugosc_okienka_na_przedziale);

		for(int j = 0; j < m - dlugosc_okienka_na_przedziale + 1; ++j)
		{
			wartosci_minimalne_w_kolumnie[j][i] = wartosci_minimalne_1D[j];
		}
	}

	vector <vector <int>> wartosci_minimalne_2D(n - szerokosc_okienka_na_przedziale + 1, vector <int> (m - dlugosc_okienka_na_przedziale + 1));

	for(int j = 0; j < m - dlugosc_okienka_na_przedziale + 1; ++j)
	{
		vector <int> wartosci_minimalne_1D = znajdz_minimum_na_okienku_1D(wartosci_minimalne_w_kolumnie[j], szerokosc_okienka_na_przedziale);

		for(int i = 0; i < n - szerokosc_okienka_na_przedziale + 1; ++i)
		{
			wartosci_minimalne_2D[i][j] = wartosci_minimalne_1D[i];
		}
	}

	return wartosci_minimalne_2D;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int szerokosc_dzialki, wysokosc_dzialki, szerokosc_machiny, wysokosc_machiny;
	cin >> szerokosc_dzialki >> wysokosc_dzialki >> szerokosc_machiny >> wysokosc_machiny;

	vector <vector <int>> liczby(szerokosc_dzialki, vector <int> (wysokosc_dzialki));

	for(int i = 0; i < szerokosc_dzialki; i++)
	{
		for(int j = 0; j < wysokosc_dzialki; j++)
		{
			cin >> liczby[i][j];
		}
	}

	vector <vector <int>> odpowiedzi = znajdz_minimum_na_okienku_2D(liczby, szerokosc_machiny, wysokosc_machiny);

	for(int i = 0; i < szerokosc_dzialki - szerokosc_machiny + 1; i++)
	{
		for(int j = 0; j < wysokosc_dzialki - wysokosc_machiny + 1; j++)
		{
			cout << odpowiedzi[i][j] << " ";
		}

		cout << "\n";
	}

	return 0;
}