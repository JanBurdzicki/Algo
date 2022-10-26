#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 5;
const int MOD = 998244353;

vector <int> graf[MAX_N];
vector <bool> visited(MAX_N);

vector <int> nimber(MAX_N);
vector <int> czy_uzyty(MAX_N);

void DFS(int v)
{
	visited[v] = true;

	for(auto& sasiad : graf[v])
	{
		if(!visited[sasiad])
		{
			DFS(sasiad);
		}
	}

	for(auto& sasiad : graf[v])
	{
		czy_uzyty[nimber[sasiad]] = v;

		while(czy_uzyty[nimber[v]] == v)
		{
			nimber[v]++;
		}
	}
}

// ! Inverse

int extended_gcd(int a, int b, long long& x, long long& y)
{
	if(b == 0)
	{
		x = 1;
		y = 0;

		return a;
	}

	long long x1, y1;
	int d = extended_gcd(b, a % b, x1, y1);

	x = y1;
	y = x1 - y1 * (a / b);

	return d;
}

int inverse(long long liczba)
{
	long long x, y;

	int g = extended_gcd(liczba, MOD, x, y);

	if(g != 1)
	{
		return 0;
	}

	x = (x % MOD + MOD) % MOD;

	return x;
}

// ! FWHT

void FWHT_XOR(vector <long long>& wielomian, int stopien_wielomianu, bool czy_odwrotna = false)
{
	long long inwersja_2 = inverse(2);

	for(int szerokosc = 2, wysokosc = 1; szerokosc <= stopien_wielomianu; szerokosc <<= 1, wysokosc <<= 1)
	{
		for(int przesuniecie = 0; przesuniecie < stopien_wielomianu; przesuniecie += szerokosc)
		{
			for(int i = 0; i < wysokosc; i++)
			{
				long long poprzednia_wartosc_komorki = wielomian[przesuniecie + wysokosc + i];

				wielomian[przesuniecie + wysokosc + i] = wielomian[przesuniecie + i] - poprzednia_wartosc_komorki;
				wielomian[przesuniecie + i] += poprzednia_wartosc_komorki;

				wielomian[przesuniecie + wysokosc + i] = (wielomian[przesuniecie + wysokosc + i] + MOD) % MOD;
				wielomian[przesuniecie + i] = (wielomian[przesuniecie + i] + MOD) % MOD;

				if(czy_odwrotna)
				{
					wielomian[przesuniecie + wysokosc + i] *= inwersja_2;

					wielomian[przesuniecie + wysokosc + i] %= MOD;

					wielomian[przesuniecie + i] *= inwersja_2;

					wielomian[przesuniecie + i] %= MOD;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
	}

	int max_nimber = -1;

	for(int i = 1; i <= n; i++)
	{
		if(!visited[i])
		{
			DFS(i);
		}

		max_nimber = max(max_nimber, nimber[i]);
	}

	// ! Liczymy XORa od korzenia do wierzcholkow i zliczamy ile jest XORow o danej wartosci

	int potega = 1;

	while(potega <= max_nimber)
	{
		potega *= 2;
	}

	vector <long long> wielomian(n);

	for(int i = 1; i <= n; i++)
	{
		wielomian[nimber[i]]++;
	}

	int inwersja = inverse(n + 1);

	for(int i = 0; i < potega; i++)
	{
		wielomian[i] = wielomian[i] * inwersja;

		wielomian[i] %= MOD;

		wielomian[i] *= -1;

		wielomian[i] = (wielomian[i] + MOD) % MOD;
	}

	wielomian[0]++;

	wielomian[0] %= MOD;

	// ! FWHT

	FWHT_XOR(wielomian, potega);

	for(int i = 0; i < potega; i++)
	{
		wielomian[i] = inverse(wielomian[i]);
	}

	FWHT_XOR(wielomian, potega, true);

	for(int i = 0; i < potega; i++)
	{
		wielomian[i] = wielomian[i] * inwersja;

		wielomian[i] %= MOD;
	}

	long long wynik = 1 - wielomian[0];

	wynik = (wynik + MOD) % MOD;

	cout << wynik << "\n";
	return 0;
}


/*

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 5;

struct Krawedz
{
	int sasiad, waga;
};

vector <Krawedz> graf[MAX_N];

void DFS(vector <long long>& wielomian, int v, int poprzednik, int XOR)
{
	// zwiekszamy wspolczynnik wielomianu

	wielomian[XOR]++;

	for(auto& krawedz : graf[v])
	{
		int sasiad = krawedz.sasiad;
		int waga = krawedz.waga;

		if(sasiad != poprzednik)
		{
			int nowy_XOR = XOR ^ waga;

			DFS(wielomian, sasiad, v, nowy_XOR);
		}
	}
}

void FWHT_XOR(vector <long long>& wielomian, int stopien_wielomianu, bool czy_odwrotna = false)
{
	for(int szerokosc = 2, wysokosc = 1; szerokosc <= stopien_wielomianu; szerokosc <<= 1, wysokosc <<= 1)
	{
		for(int przesuniecie = 0; przesuniecie < stopien_wielomianu; przesuniecie += szerokosc)
		{
			for(int i = 0; i < wysokosc; i++)
			{
				long long poprzednia_wartosc_komorki = wielomian[przesuniecie + wysokosc + i];

				wielomian[przesuniecie + wysokosc + i] = wielomian[przesuniecie + i] - poprzednia_wartosc_komorki;
				wielomian[przesuniecie + i] += poprzednia_wartosc_komorki;

				if(czy_odwrotna)
				{
					wielomian[przesuniecie + wysokosc + i] /= 2;
					wielomian[przesuniecie + i] /= 2;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, max_wartosc;
	cin >> n >> max_wartosc;

	for(int i = 0; i < n - 1; i++)
	{
		int a, b, waga;
		cin >> a >> b >> waga;

		graf[a].push_back({b, waga});
		graf[b].push_back({a, waga});
	}

	// ! Liczymy XORa od korzenia do wierzcholkow i zliczamy ile jest XORow o danej wartosci

	vector <long long> wielomian(max_wartosc);

	DFS(wielomian, 1, 1, 0);

	// ! FWHT

	FWHT_XOR(wielomian, max_wartosc);

	for(int i = 0; i < max_wartosc; i++)
	{
		wielomian[i] *= wielomian[i];
	}

	FWHT_XOR(wielomian, max_wartosc, true);

	long long wynik = 0;

	wielomian[0] -= n;

	for(int i = 0; i < max_wartosc; i++)
	{
		wielomian[i] /= 2;

		wynik += wielomian[i] * i;
	}

	cout << wynik << "\n";

	for(int i = 0; i < max_wartosc; i++)
	{
		cout << wielomian[i] << " ";
	}

	cout << "\n";
	return 0;
}


*/