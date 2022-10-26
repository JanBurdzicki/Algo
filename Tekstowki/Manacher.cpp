#include <bits/stdc++.h>
using namespace std;

// ! Algorytm Manachera - obliczanie promieni palindromow

vector <int> Manacher_palindromy_parzyste(string s)
{
	// '$' i '#' sa znakami specjalnymi

	string x("$");
	x += s;
	x += '#';

	vector <int> R;

	R.push_back(0);

	int i = 1, j = 0;

	while(i <= (int) x.size() - 1)
	{
		while(x[i - j] == x[i + j + 1])
		{
			j++;
		}

		R.push_back(j);

		int k = 1;

		while(R[i - k] != R[i] - k && k <= j)
		{
			R.push_back(min(R[i - k], R[i] - k));

			k++;
		}

		j = max(j - k, 0);
		i += k;
	}

	return R;
}

vector <int> Manacher_palindromy_nieparzyste(string s)
{
	// '$' i '#' sa znakami specjalnymi

	string x("$");
	x += s;
	x += '#';

	vector <int> R;

	R.push_back(0);

	int i = 1, j = 0;

	while(i <= (int) x.size() - 1)
	{
		while(x[i - j - 1] == x[i + j + 1])
		{
			j++;
		}

		R.push_back(j);

		int k = 1;

		while(R[i - k] != R[i] - k && k <= j)
		{
			R.push_back(min(R[i - k], R[i] - k));
			k++;
		}

		j = max(j - k, 0);
		i += k;
	}

	return R;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	// TODO: naklepac jeszcze drzewo przedzialowe i kolejke monotoniczna

	vector <int> palindromy_parzyste = Manacher_palindromy_parzyste(s);

	int rozmiar = (int) s.size();

	bool ok = false;

	int pozycja_poczatkowa;
	int dlugosc_palindromu;
	int pozycja_dokad_siega_palindrom = -1;

	for(int i = 1; i <= rozmiar; i++)
	{
		if(pozycja_dokad_siega_palindrom >= i && palindromy_parzyste[i] > 0)
		{
			ok = true;

			dlugosc_palindromu = i - pozycja_poczatkowa;

			break;
		}

		if(pozycja_dokad_siega_palindrom < i + palindromy_parzyste[i])
		{
			pozycja_poczatkowa = i;

			pozycja_dokad_siega_palindrom = i + palindromy_parzyste[i];
		}
	}

	if(ok)
	{
		cout << "TAK\n";

		string wynik = s.substr(pozycja_poczatkowa - dlugosc_palindromu, 3 * dlugosc_palindromu);

		cout << wynik << "\n";
	}

	else
	{
		cout << "NIE\n";
	}

	return 0;
}
