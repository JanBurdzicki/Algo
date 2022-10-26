#include <bits/stdc++.h>
using namespace std;

struct Punkt
{
	int x, y;
};

struct Prostokat
{
	Punkt L, R;
};

struct Hasze_2D
{
	static const int MAX_N = 1e3 + 5;
	static const int MOD = 1e9 + 7;

	static const int p = 31;
	static const int q = 37;

	static vector <long long> potegi_liczby_p;
	static vector <long long> potegi_liczby_q;

	vector <vector <long long>> sumy_prefiksowe_2D;

	int szerokosc, wysokosc;

	static void preprocessing()
	{
		potegi_liczby_p.resize(MAX_N);
		potegi_liczby_q.resize(MAX_N);

		potegi_liczby_p[0] = 1;
		potegi_liczby_q[0] = 1;

		for(int i = 1; i < MAX_N; i++)
		{
			potegi_liczby_p[i] = (potegi_liczby_p[i - 1] * p) % MOD;
			potegi_liczby_q[i] = (potegi_liczby_q[i - 1] * q) % MOD;
		}
	}

	Hasze_2D(vector <string>& tekst)
	{
		this->szerokosc = (int) tekst.size();
		this->wysokosc = (int) tekst[0].size();

		sumy_prefiksowe_2D.resize(szerokosc + 1, vector <long long> (wysokosc + 1));

		for(int i = 1; i <= szerokosc; i++)
		{
			for(int j = 1; j <= wysokosc; j++)
			{
				sumy_prefiksowe_2D[i][j] = ((((tekst[i - 1][j - 1] - 'a' + 1) * potegi_liczby_p[i]) % MOD) * potegi_liczby_q[j]) % MOD;

				sumy_prefiksowe_2D[i][j] = (sumy_prefiksowe_2D[i][j] + sumy_prefiksowe_2D[i][j - 1] + sumy_prefiksowe_2D[i - 1][j] - sumy_prefiksowe_2D[i - 1][j - 1] + MOD) % MOD;
			}
		}
	}

	long long policz_hasz_prostokata(int x_1, int y_1, int x_2, int y_2)
	{
		long long wynik = ((sumy_prefiksowe_2D[x_2][y_2] - sumy_prefiksowe_2D[x_1 - 1][y_2] - sumy_prefiksowe_2D[x_2][y_1 - 1] + sumy_prefiksowe_2D[x_1 - 1][y_1 - 1]) % MOD + MOD) % MOD;

		return wynik;
	}

	long long policz_hasz_prostokata(Prostokat prostokat)
	{
		return policz_hasz_prostokata(prostokat.L.x, prostokat.L.y, prostokat.R.x, prostokat.R.y);
	}

	long long policz_hasz_prostokata()
	{
		return policz_hasz_prostokata(1, 1, szerokosc, wysokosc);
	}

	long long policz_przesuniety_hasz(long long hasz, int indeks_1, int indeks_2)
	{
		long long wynik = (((hasz * potegi_liczby_p[indeks_1]) % MOD) * potegi_liczby_q[indeks_2]) % MOD;

		return wynik;
	}
};

void Rabin_Karp(Hasze_2D& hasze_tekstu, Hasze_2D& hasze_wzorca, vector <Punkt>& indeksy_wystapien)
{
	int szerokosc_tekstu = hasze_tekstu.szerokosc;
	int wysokosc_tekstu = hasze_tekstu.wysokosc;

	int szerokosc_wzorca = hasze_wzorca.szerokosc;
	int wysokosc_wzorca = hasze_wzorca.wysokosc;

	long long hasz_wzorca = hasze_wzorca.policz_hasz_prostokata();

	for(int i = 1; i + szerokosc_wzorca - 1 <= szerokosc_tekstu; i++)
	{
		for(int j = 1; j + wysokosc_wzorca - 1 <= wysokosc_tekstu; j++)
		{
			long long hasz_prostokata = hasze_tekstu.policz_hasz_prostokata(i, j, i + szerokosc_wzorca - 1, j + wysokosc_wzorca - 1);

			long long nowy_hasz_wzorca = hasze_wzorca.policz_przesuniety_hasz(hasz_wzorca, i - 1, j - 1);

			if(hasz_prostokata == nowy_hasz_wzorca)
			{
				indeksy_wystapien.push_back({i, j});
			}
		}
	}
}

bool czy_rowne_prostokaty(Hasze_2D& hasze_tekstu, Prostokat& prostokat_1, Prostokat& prostokat_2)
{
	int szerokosc_1 = prostokat_1.R.x - prostokat_1.L.x + 1;
	int wysokosc_1 = prostokat_1.R.y - prostokat_1.L.y + 1;

	int szerokosc_2 = prostokat_2.R.x - prostokat_2.L.x + 1;
	int wysokosc_2 = prostokat_2.R.y - prostokat_2.L.y + 1;

	if(szerokosc_1 == szerokosc_2 && wysokosc_1 == wysokosc_2)
	{
		long long hasz_prostokata_1 = hasze_tekstu.policz_hasz_prostokata(prostokat_1);
		long long hasz_prostokata_2 = hasze_tekstu.policz_hasz_prostokata(prostokat_2);

		int dx = prostokat_2.L.x - prostokat_1.L.x;
		int dy = prostokat_2.L.y - prostokat_1.L.y;

		int dx_1 = 0, dy_1 = 0;
		int dx_2 = 0, dy_2 = 0;

		// prostokat_1 jest po prawej stronie prostokat_2
		if(dx < 0)
		{
			dx_2 = -dx;
		}

		// prostokat_1 jest po lewej stronie prostokat_2
		else
		{
			dx_1 = dx;
		}

		// prostokat_1 jest ponizej prostokat_2
		if(dy < 0)
		{
			dy_2 = -dy;
		}

		// prostokat_1 jest powyzej prostokat_2
		else
		{
			dy_1 = dy;
		}

		long long nowy_hasz_prostokata_1 = hasze_tekstu.policz_przesuniety_hasz(hasz_prostokata_1, dx_1, dy_1);
		long long nowy_hasz_prostokata_2 = hasze_tekstu.policz_przesuniety_hasz(hasz_prostokata_2, dx_2, dy_2);

		if(nowy_hasz_prostokata_1 == nowy_hasz_prostokata_2)
		{
			return true;
		}
	}

	return false;
}

vector <long long> Hasze_2D::potegi_liczby_p{};
vector <long long> Hasze_2D::potegi_liczby_q{};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int szerokosc_tekstu, wysokosc_tekstu;
	cin >> szerokosc_tekstu >> wysokosc_tekstu;

	Hasze_2D::preprocessing();

	vector <string> tekst(szerokosc_tekstu);

	for(int i = 0; i < szerokosc_tekstu; i++)
	{
		cin >> tekst[i];
	}

	Hasze_2D hasze_tekstu(tekst);

	int t;
	cin >> t;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int szerokosc_wzorca, wysokosc_wzorca;
		cin >> szerokosc_wzorca >> wysokosc_wzorca;

		vector <string> wzorzec(szerokosc_wzorca);

		for(int i = 0; i < szerokosc_wzorca; i++)
		{
			cin >> wzorzec[i];
		}

		Hasze_2D hasze_wzorca(wzorzec);

		vector <Punkt> indeksy_wystapien;

		Rabin_Karp(hasze_tekstu, hasze_wzorca, indeksy_wystapien);

		cout << (int) indeksy_wystapien.size() << "\n";

		for(auto& odp : indeksy_wystapien)
		{
			cout << odp.x << " " << odp.y << "\n";
		}
	}

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		Prostokat prostokat_1, prostokat_2;
		cin >> prostokat_1.L.x >> prostokat_1.L.y >> prostokat_1.R.x >> prostokat_1.R.y;
		cin >> prostokat_2.L.x >> prostokat_2.L.y >> prostokat_2.R.x >> prostokat_2.R.y;

		if(czy_rowne_prostokaty(hasze_tekstu, prostokat_1, prostokat_2))
		{
			cout << "TAK\n";
		}

		else
		{
			cout << "NIE\n";
		}
	}

	return 0;
}