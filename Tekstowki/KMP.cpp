#include <bits/stdc++.h>
using namespace std;

vector <int> prefix_function(string& s, int n)
{
	vector <int> dlugosci_prefikso_sufiksow(n);

	dlugosci_prefikso_sufiksow[0] = 0;

	for(int i = 1; i < n; i++)
	{
		dlugosci_prefikso_sufiksow[i] = dlugosci_prefikso_sufiksow[i-1];

		while(dlugosci_prefikso_sufiksow[i] && s[dlugosci_prefikso_sufiksow[i]] != s[i])
		{
			dlugosci_prefikso_sufiksow[i] = dlugosci_prefikso_sufiksow[dlugosci_prefikso_sufiksow[i] - 1];
		}

		if(s[i] == s[dlugosci_prefikso_sufiksow[i]])
		{
			dlugosci_prefikso_sufiksow[i]++;
		}
	}

	return dlugosci_prefikso_sufiksow;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	string s;
	cin >> s;

	vector <int> dlugosci_prefikso_sufiksow = prefix_function(s, n);

	for(int i = 0; i < n; i++)
	{
		cout << dlugosci_prefikso_sufiksow[i] << " ";
	}

	cout << "\n";

	// wzorzec + '#' + tekst
	// Wtedy jesli dlugosci_prefikso_sufiksow[i] == n, to na pozycji i - 2 * n jest poczatek wystapienia wzorca
	// Jesli mamy malo dostepnej pamieci, to mozemy miec stringa = wzorzec + '#' i wczytywac po jednej literce tekstu
	// Liczyc dpeka dla danej literki, itd.
	// Zlozonosc czasowa: O(n + m)
	// Zlozonosc pamieciowa: O(n)

	return 0;
}