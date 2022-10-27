#include <bits/stdc++.h>
using namespace std;

struct Funkcja_Z
{
	vector <int> wartosci_funkcji_z;

	Funkcja_Z(string& s)
	{
		int n = (int) s.size();

		wartosci_funkcji_z.resize(n);

		int L = 0, R = 0;

		for(int i = 1; i < n; i++)
		{
			if(i <= R)
			{
				int dlugosc_przedzialu = R - i + 1;

				wartosci_funkcji_z[i] = min(dlugosc_przedzialu, wartosci_funkcji_z[i - L]);
			}

			while(i + wartosci_funkcji_z[i] < n && s[wartosci_funkcji_z[i]] == s[i + wartosci_funkcji_z[i]])
			{
				wartosci_funkcji_z[i]++;
			}

			if(i + wartosci_funkcji_z[i] - 1 > R)
			{
				L = i;
				R = i + wartosci_funkcji_z[i] - 1;
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	Funkcja_Z funkcja_z(s);

	for(int i = 0; i < (int) s.size(); i++)
	{
		cout << funkcja_z.wartosci_funkcji_z[i] << " ";
	}

	cout << "\n";

/*
	const int INF = 1e9 + 5;

	string wzorzec;
	cin >> wzorzec;

	string tekst;
	cin >> tekst;

	int rozmiar_wzorca = (int) wzorzec.size();
	int rozmiar_tekstu = (int) tekst.size();

	string wzorzec_prefiks = wzorzec;
	string wzorzec_sufiks = wzorzec;

	string tekst_prefiks = tekst;
	string tekst_sufiks = tekst;

	reverse(wzorzec_sufiks.begin(), wzorzec_sufiks.end());
	reverse(tekst_sufiks.begin(), tekst_sufiks.end());

	string s_prefiks = wzorzec_prefiks + '#' + tekst_prefiks;
	string s_sufiks = wzorzec_sufiks + '#' + tekst_sufiks;

	Funkcja_Z funkcja_z_prefiks(s_prefiks);
	Funkcja_Z funkcja_z_sufiks(s_sufiks);

	int wynik = INF;

	int start = rozmiar_wzorca + 1;
	int koniec = rozmiar_tekstu + 1;

	for(int i = rozmiar_wzorca + 1; i <= rozmiar_tekstu + 1; i++)
	{
		int indeks_L = i;
		int indeks_R = rozmiar_tekstu + rozmiar_wzorca + 2 - i;

		int L = funkcja_z_prefiks.wartosci_funkcji_z[indeks_L];
		int R = funkcja_z_sufiks.wartosci_funkcji_z[indeks_R];

		int dlugosc_przedzialu = max(rozmiar_wzorca - R - L, 0);

		wynik = min(wynik, dlugosc_przedzialu);
	}

	cout << wynik << "\n";
*/
	return 0;
}
