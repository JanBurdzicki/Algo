#include <bits/stdc++.h>
using namespace std;

// TODO: jak znajde cos lepszego to poprawic

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, szukana_liczba;
	cin >> n >> szukana_liczba;

	// program sprawdzajacy min dlugosc przedzialu, ktorego suma == szukana_liczba

	vector <int> sumy_prefiksowe(n + 1);

	for(int i = 1; i <= n; i++)
	{
		int liczba;
		cin >> liczba;

		sumy_prefiksowe[i] = sumy_prefiksowe[i - 1] + liczba;
	}

	int L = 1, R = 1;

	int wynik = INT_MAX;

	while(R <= n)
	{
		// jesli suma na przedziale jest za mala
		while(sumy_prefiksowe[R] - sumy_prefiksowe[L - 1] < szukana_liczba && R <= n)
		{
			R++;
		}

		// jesli suma na przedziale jest rowna szukana_liczba
		if(R <= n && sumy_prefiksowe[R] - sumy_prefiksowe[L - 1] == szukana_liczba)
		{
			wynik = min(wynik, R - L + 1);

			L++;
		}

		// jesli suma na przedziale jest za duza
		while(sumy_prefiksowe[R] - sumy_prefiksowe[L - 1] > szukana_liczba)
		{
			L++;
		}
	}

	if(wynik == INT_MAX)
	{
		cout << "-1\n";
	}

	else
	{
		cout << wynik << "\n";
	}

	return 0;
}
