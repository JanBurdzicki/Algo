#include <bits/stdc++.h>
using namespace std;

const int MAX_WARTOSC = 1e6 + 5;
const int INF = 1e9 + 5;

// Zlozonosc czasowa: O(n log n)
// Zlozonosc pamieciowa: O(MAX_WARTOSC) z odzyskaniem LISu, lub O(n) bez odzyskiwania
// LIS - jako najdluszy podciag niemalejacy
// UWAGA! Jesli ma byc najdluzszy podciag rosnacy, to zamieniamy lower_bound() na upper_bound() -> TODO: sprawdzic czy 2 ostatnie linie komentarzy sa poprawne
// TODO: napisac o double

void LIS(vector <int>& liczby, int n)
{
	// dp[i] to element, na ktory konczy sie LIS o dlugosci i
	// indeksy_elementow[i] to indeks elementu, ktory znajduje sie w dp[i]
	// poprzedni[liczby[i]] to indeks elementu poprzedniego w LISie
	vector <int> dp(n + 1, INF), indeksy_elementow(n + 1, INF), poprzedni(n + 1);

	dp[0] = -INF;

	for(int i = 0; i < n; i++)
	{
		int indeks = lower_bound(dp.begin(), dp.end(), liczby[i]) - dp.begin();

		dp[indeks] = liczby[i];
		indeksy_elementow[indeks] = i;
		poprzedni[i] = indeksy_elementow[indeks - 1];
	}

	int wynik = 0;

	for(int i = 0; i <= n; i++)
	{
		if(dp[i] < INF)
		{
			wynik = i;
		}
	}

	// odzyskiwanie LISu

	vector <int> podciag;

	int pozycja = indeksy_elementow[wynik];

	while(pozycja != INF)
	{
		podciag.push_back(liczby[pozycja]);
		pozycja = poprzedni[pozycja];
	}

	reverse(podciag.begin(), podciag.end());

	cout << wynik << "\n";

	for(auto& x : podciag)
	{
		cout << x << " ";
	}

	cout << "\n";
}

void LDS(vector <int>& liczby, int n)
{
	for(int i = 0; i < n; i++)
	{
		liczby[i] *= -1;
	}

	LIS(liczby, n);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <int> liczby(n);

	for(int i = 0; i < n; i++)
	{
		cin >> liczby[i];
	}

	LIS(liczby, n);

	LDS(liczby, n);

	return 0;
}
