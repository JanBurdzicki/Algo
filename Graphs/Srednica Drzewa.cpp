#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;

vector <int> graf[MAX_N];
vector <int> dist(MAX_N);

void DFS(int v, int poprzednik, int& max_odleglosc, int& max_wierzcholek)
{
	if(dist[v] > max_odleglosc)
	{
		max_odleglosc = dist[v];

		max_wierzcholek = v;
	}

	for(auto& sasiad : graf[v])
	{
		if(sasiad != poprzednik)
		{
			dist[sasiad] = dist[v] + 1;

			DFS(sasiad, v, max_odleglosc, max_wierzcholek);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for(int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	int max_wierzcholek = 1;
	int max_odleglosc = -1;

	DFS(max_wierzcholek, -1, max_odleglosc, max_wierzcholek);

	dist[max_wierzcholek] = 0;

	max_odleglosc = -1;

	DFS(max_wierzcholek, -1, max_odleglosc, max_wierzcholek);

	cout << max_odleglosc << "\n";
	return 0;
}

// TODO: mozna dodac jeszcze zapamietywanie koncow srednicy
