#include <bits/stdc++.h>
using namespace std;

// Zauwazmy, ze INF musi byc wiekszy od MAX_WARTOSC + log(n)
const int INF = 2e9 + 5;
const int MOD = 1e9 + 7;

struct Przedzial
{
	int L, R;

	bool operator < (const Przedzial& inny) const
	{
		if(L != inny.L)
		{
			return L < inny.L;
		}

		else
		{
			return R < inny.R;
		}
	}

	bool operator == (const Przedzial& inny) const
	{
		return (L == inny.L && R == inny.R);
	}
};

struct Macierz
{
	// macierz[x][y] = macierz[najbardziej na prawo bit, ktorego nie musimy zmieniac][najbardziej na lewo bit, ktorego nie musimy zmieniac]
	int macierz[2][2];

	Macierz()
	{
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				macierz[i][j] = 0;
			}
		}
	}

	int* operator [] (int indeks)
	{
		return macierz[indeks];
	}

	const int* operator [] (int indeks) const
	{
		return macierz[indeks];
	}

	Macierz operator * (const Macierz& inny) const
	{
		Macierz wynik;

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				for(int k = 0; k < 2; k++)
				{
					wynik[i][k] = (wynik[i][k] + 1LL * macierz[i][j] * inny.macierz[j][k]) % MOD;
				}
			}
		}

		return wynik;
	}
};

struct Wierzcholek
{
	bool czy_istnieje = false;

	int najbardziej_na_lewo, najbardziej_na_prawo;

	Macierz macierz;

	void init(Przedzial przedzial)
	{
		najbardziej_na_lewo = przedzial.L, najbardziej_na_prawo = przedzial.R;

		int rozmiar = (najbardziej_na_prawo - najbardziej_na_lewo) / 2 + 1;

		macierz[0][0] = 1;
		macierz[0][1] = 0;
		macierz[1][0] = rozmiar - 1;
		macierz[1][1] = 1;
	}

	void combine(const Wierzcholek& a, const Wierzcholek& b)
	{
		czy_istnieje = a.czy_istnieje || b.czy_istnieje;

		if(!a.czy_istnieje)
		{
			*this = b;

			return;
		}

		if(!b.czy_istnieje)
		{
			*this = a;

			return;
		}

		najbardziej_na_lewo = a.najbardziej_na_lewo;
		najbardziej_na_prawo = b.najbardziej_na_prawo;

		const int odleglosc = b.najbardziej_na_lewo - a.najbardziej_na_prawo;

		Macierz	mid;

		if(odleglosc % 2 == 0)
		{
			mid[0][0] = 1;
			mid[1][0] = 1;
		}

		mid[0][1] = max(0, (odleglosc - 1) / 2);
		mid[1][1] = max(0, (odleglosc - 1) / 2);

		mid[1][1] = (mid[1][1] + 1) % MOD;

		macierz = (b.macierz * mid) * a.macierz;
	}
};

set <Przedzial> przedzialy;

vector <vector <Przedzial>> wydarzenia;

int timer;

void dodaj_jesli_niepuste(int L, int R)
{
	if(L <= R)
	{
		wydarzenia[timer].push_back({L, R});

		przedzialy.insert({L, R});
	}
}

void usun(set <Przedzial>::iterator it)
{
	wydarzenia[timer].push_back({it->L, it->R});

	przedzialy.erase(it);
}

void dodaj_na_zewnatrz(const int liczba)
{
	auto R = przedzialy.upper_bound({liczba, INF});

	if(liczba + 1 == R->L)
	{
		// tuz przed przedzialem R
		// caly przedzial kompresowujemy do R->R + 1

		const int nowa_wartosc = R->R + 1;

		usun(R);

		dodaj_na_zewnatrz(nowa_wartosc);

		return;
	}

	auto L = prev(R);

	if(L->R + 1 == liczba)
	{
		// tuz za przedzialem L
		// usuwamy ostatni element przedzialu L

		dodaj_jesli_niepuste(L->L, L->R - 2);

		usun(L);

		dodaj_na_zewnatrz(liczba + 1);

		return;
	}

	Przedzial nowy_przedzial = {liczba, liczba};

	if(liczba + 2 == R->L)
	{
		nowy_przedzial.R = R->R;

		usun(R);
	}

	if(L->R + 2 == liczba)
	{
		nowy_przedzial.L = L->L;

		usun(L);
	}

	dodaj_jesli_niepuste(nowy_przedzial.L, nowy_przedzial.R);
}

void dodaj_mozliwe_do_wewnatrz(const int liczba)
{
	auto it = przedzialy.upper_bound({liczba, INF});

	it--;

	if(!(it->L <= liczba && liczba <= it->R))
	{
		dodaj_na_zewnatrz(liczba);

		return;
	}

	// Teraz juz wiemy, ze liczba jest w przedziale

	if(it->L % 2 != liczba % 2)
	{
		// Mamy przypadek dodania do 0 w ciagu ...01010...

		//   ...001010101010100...
		// +            1
		// = ...001010100000010...

		dodaj_jesli_niepuste(it->L, liczba - 1);

		const int nowa_wartosc = it->R + 1;

		usun(it);

		dodaj_na_zewnatrz(nowa_wartosc);
	}

	else
	{
		// Mamy przypadek dodania do 1 w ciagu ...01010...

		//   ...001010101010100...
		// +           1
		// = ...100101011010100...
		// = ...100101000000010...

		const vector <int> nowe_wartosci = {it->L - 2, it->R + 1};

		dodaj_jesli_niepuste(it->L + 1, liczba - 1);

		usun(it);

		for(auto a : nowe_wartosci)
		{
			if(a == -2)
			{
				// Fibonacci[-2] = 0

				continue;
			}

			if(a == -1)
			{
				// Fibonacci[-1] = Fibonacci[0]

				a = 0;
			}

			dodaj_na_zewnatrz(a);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	wydarzenia.resize(n);

	// Dla latwiejszej implementacji dodajemy dwa przedzialy

	przedzialy.insert({-INF, -INF});
	przedzialy.insert({INF, INF});

	for(timer = 0; timer < n; timer++)
	{
		int liczba;
		cin >> liczba;

		liczba--;

		dodaj_mozliwe_do_wewnatrz(liczba);
	}

	vector <Przedzial> wszystkie;

	for(auto& wydarzenie : wydarzenia)
	{
		for(auto& x : wydarzenie)
		{
			wszystkie.push_back(x);
		}
	}

	sort(wszystkie.begin(), wszystkie.end());

	wszystkie.resize(unique(wszystkie.begin(), wszystkie.end()) - wszystkie.begin());

	int potega = 1;

	while(potega < (int) wszystkie.size())
	{
		potega *= 2;
	}

	vector <Wierzcholek> segtree(2 * potega);

	for(int i = 0; i < (int) wszystkie.size(); i++)
	{
		segtree[potega + i].init(wszystkie[i]);
	}

	Wierzcholek start;

	start.init({-1, -1});
	start.czy_istnieje = true;

	for(timer = 0; timer < n; timer++)
	{
		for(auto& x : wydarzenia[timer])
		{
			int pozycja = lower_bound(wszystkie.begin(),wszystkie.end(), x) - wszystkie.begin();

			segtree[potega + pozycja].czy_istnieje = !segtree[potega + pozycja].czy_istnieje;

			for(int i = (potega + pozycja) / 2; i >= 1; i /= 2)
			{
				segtree[i].combine(segtree[2 * i], segtree[2 * i + 1]);
			}
		}

		Wierzcholek wynik;

		wynik.combine(start, segtree[1]);

		cout << wynik.macierz[1][1] << "\n";
	}

	return 0;
}