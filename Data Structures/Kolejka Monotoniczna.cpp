#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

struct Element
{
	int wartosc, indeks;
};

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

	stack <Element> kolejna_monotoniczna;

	kolejna_monotoniczna.push({INF, -1});

	for(int i = 0; i < n; i++)
	{
		while(kolejna_monotoniczna.top().wartosc <= liczby[i])
		{
			kolejna_monotoniczna.pop();
		}

		cout << kolejna_monotoniczna.top().indeks << "\n";

		kolejna_monotoniczna.push({liczby[i], i + 1});
	}

	return 0;
}