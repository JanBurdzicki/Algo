#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int LOG = 31;

int up[MAX_N][LOG];
vector <int> kiedy(MAX_N);

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, t;
	cin >> n >> t;

	vector <int> liczby(n);

	vector <int> pozycje_startowe;

	for(int i = 0; i < n; i++)
	{
		cin >> liczby[i];

		if(liczby[i] == 1)
		{
			pozycje_startowe.push_back(i);
		}
	}

	for(int i = n - 1; i >= 0; i--)
	{
		if(kiedy[liczby[i] + 1] > 0)
		{
			up[i][0] = kiedy[liczby[i] + 1];
		}

		else
		{
			up[i][0] = n;
		}

		kiedy[liczby[i]] = i;
	}

	for(int i = 0; i < LOG; i++)
	{
		up[n][i] = n;
	}

	for(int i = 1; i < LOG; i++)
	{
		for(int j = 0; j < n; j++)
		{
			up[j][i] = up[up[j][i - 1]][i - 1];
		}
	}

	for(int i = 0; i < t; i++)
	{
		int L, R;
		cin >> L >> R;

		L--;
		R--;

		auto it = lower_bound(pozycje_startowe.begin(), pozycje_startowe.end(), L);

		if(it == pozycje_startowe.end())
		{
			cout << "0\n";
			continue;
		}

		int wynik = 1;

		int indeks = it - pozycje_startowe.begin();

		int aktualna = pozycje_startowe[indeks];

		for(int j = LOG - 1; j >= 0; j--)
		{
			if(up[aktualna][j] <= R)
			{
				aktualna = up[aktualna][j];

				wynik += (1 << j);
			}
		}

		cout << wynik << "\n";
	}

	return 0;
}