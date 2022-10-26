#include <bits/stdc++.h>
using namespace std;

struct Hasze
{
	static const int MAX_N = 1e5 + 5;
	static const int MOD = 1e9 + 7;

	static const int p = 31;

	struct Przedzial
	{
		int L, R;
	};

	static vector <long long> potegi_liczby_p;

	vector <long long> sumy_prefiksowe;

	int rozmiar;

	static void preprocessing()
	{
		potegi_liczby_p.resize(MAX_N);

		potegi_liczby_p[0] = 1;

		for(int i = 1; i < MAX_N; i++)
		{
			potegi_liczby_p[i] = (potegi_liczby_p[i - 1] * p) % MOD;
		}
	}

	Hasze(string& tekst)
	{
		this->rozmiar = (int) tekst.size();

		sumy_prefiksowe.resize(rozmiar + 1);

		for(int i = 1; i <= rozmiar; i++)
		{
			sumy_prefiksowe[i] = ((tekst[i - 1] - 'a' + 1) * potegi_liczby_p[i]) % MOD;

			sumy_prefiksowe[i] = (sumy_prefiksowe[i] + sumy_prefiksowe[i - 1]) % MOD;
		}
	}

	long long policz_hasz_przedzialu(int L, int R)
	{
		long long wynik = ((sumy_prefiksowe[R] - sumy_prefiksowe[L - 1]) % MOD + MOD) % MOD;

		return wynik;
	}

	long long policz_hasz_przedzialu(Przedzial przedzial)
	{
		return policz_hasz_przedzialu(przedzial.L, przedzial.R);
	}

	long long policz_hasz_przedzialu()
	{
		return policz_hasz_przedzialu(1, rozmiar);
	}

	long long policz_przesuniety_hasz(long long hasz, int indeks)
	{
		long long wynik = (hasz * potegi_liczby_p[indeks]) % MOD;

		return wynik;
	}
};

void Rabin_Karp(Hasze& hasze_tekstu, Hasze& hasze_wzorca, vector <int>& indeksy_wystapien)
{
	int rozmiar_tekstu = hasze_tekstu.rozmiar;
	int rozmiar_wzorca = hasze_wzorca.rozmiar;

	long long hasz_wzorca = hasze_wzorca.policz_hasz_przedzialu();

	for(int i = 1; i + rozmiar_wzorca - 1 <= rozmiar_tekstu; i++)
	{
		long long hasz_przedzialu = hasze_tekstu.policz_hasz_przedzialu(i, i + rozmiar_wzorca - 1);

		long long nowy_hasz_wzorca = hasze_wzorca.policz_przesuniety_hasz(hasz_wzorca, i - 1);

		if(hasz_przedzialu == nowy_hasz_wzorca)
		{
			indeksy_wystapien.push_back(i);
		}
	}
}

bool czy_rowne_prostokaty(Hasze& hasze_1, Hasze& hasze_2, Hasze::Przedzial przedzial_1, Hasze::Przedzial przedzial_2)
{
	int szerokosc_1 = przedzial_1.R - przedzial_1.L + 1;
	int szerokosc_2 = przedzial_2.R - przedzial_2.L + 1;

	if(szerokosc_1 == szerokosc_2)
	{
		long long hasz_przedzialu_1 = hasze_1.policz_hasz_przedzialu(przedzial_1);
		long long hasz_przedzialu_2 = hasze_2.policz_hasz_przedzialu(przedzial_2);

		int dx = przedzial_2.L - przedzial_1.L;

		int dx_1 = 0;
		int dx_2 = 0;

		// przedzial_1 jest po prawej stronie przedzial_2
		if(dx < 0)
		{
			dx_2 = -dx;
		}

		// przedzial_1 jest po lewej stronie przedzial_2
		else
		{
			dx_1 = dx;
		}

		long long nowy_hasz_przedzialu_1 = hasze_1.policz_przesuniety_hasz(hasz_przedzialu_1, dx_1);
		long long nowy_hasz_przedzialu_2 = hasze_2.policz_przesuniety_hasz(hasz_przedzialu_2, dx_2);

		if(nowy_hasz_przedzialu_1 == nowy_hasz_przedzialu_2)
		{
			return true;
		}
	}

	return false;
}

vector <long long> Hasze::potegi_liczby_p{};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int rozmiar_tekstu;
	cin >> rozmiar_tekstu;

	Hasze::preprocessing();

	string tekst;
	cin >> tekst;

	Hasze hasze_tekstu(tekst);

	int t;
	cin >> t;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int rozmiar_wzorca;
		cin >> rozmiar_wzorca;

		string wzorzec;
		cin >> wzorzec;

		Hasze hasze_wzorca(wzorzec);

		vector <int> indeksy_wystapien;

		Rabin_Karp(hasze_tekstu, hasze_wzorca, indeksy_wystapien);

		cout << (int) indeksy_wystapien.size() << "\n";

		for(auto& odp : indeksy_wystapien)
		{
			cout << odp << "\n";
		}
	}

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		Hasze::Przedzial przedzial_1, przedzial_2;
		cin >> przedzial_1.L >> przedzial_1.R;
		cin >> przedzial_2.L >> przedzial_2.R;

		if(czy_rowne_prostokaty(hasze_tekstu, hasze_tekstu, przedzial_1, przedzial_2))
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