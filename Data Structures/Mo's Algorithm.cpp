#include <bits/stdc++.h>
using namespace std;

// TODO: zrobic templetami structy i funkcje, bedzie latwiej potem

const int MAX_N = 1e5 + 5;
const int SQRT = 316;

// SQRT to szerokosc paska

struct Zapytanie
{
	int L, R, indeks;

	bool operator < (const Zapytanie& inny) const
	{
		int pasek_1 = L / SQRT;
		int pasek_2 = inny.L / SQRT;

		if(pasek_1 != pasek_2)
		{
			return pasek_1 < pasek_2;
		}

		else
		{
			if(pasek_1 % 2 == 0)
			{
				return R < inny.R;
			}

			else
			{
				return R > inny.R;
			}
		}
	}
};

struct Wynik
{
	int wartosc, ilosc_wystapien;

	bool operator < (const Wynik& inny) const
	{
		if(ilosc_wystapien != inny.ilosc_wystapien)
		{
			return ilosc_wystapien < inny.ilosc_wystapien;
		}

		else
		{
			return wartosc > inny.wartosc;
		}
	}
};

struct Mo_Algorithm
{
	vector <int> ilosci_wystapien = vector <int> (MAX_N);

	set <Wynik> secik;

	Wynik aktualny_wynik;

	int L, R;

	void dodaj_wartosc(int wartosc)
	{
		// Dodajemy wartosc -> przy rozszerzaniu przedzialu

		secik.erase({wartosc, ilosci_wystapien[wartosc]});

		ilosci_wystapien[wartosc]++;

		secik.insert({wartosc, ilosci_wystapien[wartosc]});
	}

	void usun_wartosc(int wartosc)
	{
		// Usuwamy wartosc -> przy zwezaniu przedzialu

		secik.erase({wartosc, ilosci_wystapien[wartosc]});

		ilosci_wystapien[wartosc]--;

		secik.insert({wartosc, ilosci_wystapien[wartosc]});
	}

	Wynik policz_wynik()
	{
		Wynik wynik;

		return wynik;
	}

	Wynik query(vector <Zapytanie>& zapytania, vector <int>& liczby, int indeks)
	{
		while(L > zapytania[indeks].L)
		{
			// Rozszerzamy przedzial w lewo

			L--;

			dodaj_wartosc(liczby[L]);
		}

		while(R < zapytania[indeks].R)
		{
			// Rozszerzamy przedzial w prawo

			R++;

			dodaj_wartosc(liczby[R]);
		}

		while(L < zapytania[indeks].L)
		{
			// Zwezamy przedzial w prawo

			usun_wartosc(liczby[L]);

			L++;
		}

		while(R > zapytania[indeks].R)
		{
			// Zwezamy przedzial w lewo

			usun_wartosc(liczby[R]);

			R--;
		}

		Wynik wynik = policz_wynik();

		return wynik;
	}

	// SQRT Decomposition -> Algorytm Mo
	void Algorytm_Mo(vector <int>& liczby, vector <Zapytanie>& zapytania, vector <Wynik>& odpowiedzi, int t)
	{
		sort(zapytania.begin(), zapytania.end());

		// Zaczynamy z pustym przedzialem

		L = 1;
		R = 0;

		for(int i = 0; i < t; i++)
		{
			odpowiedzi[zapytania[i].indeks] = query(zapytania, liczby, i);
		}
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, t;
	cin >> n >> t;

	vector <int> liczby(n + 1);

	for(int i = 1; i <= n; i++)
	{
		cin >> liczby[i];
	}

	vector <Zapytanie> zapytania(t);

	for(int i = 0; i < t; i++)
	{
		cin >> zapytania[i].L >> zapytania[i].R;

		zapytania[i].indeks = i;
	}

	vector <Wynik> odpowiedzi(t);

	Mo_Algorithm algorytm_Mo;

	algorytm_Mo.Algorytm_Mo(liczby, zapytania, odpowiedzi, t);

	for(auto& odp : odpowiedzi)
	{
		cout << odp.wartosc << " " << odp.ilosc_wystapien << "\n";
	}

	return 0;
}