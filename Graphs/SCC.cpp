#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

vector <int> graf[MAX_N];
vector <int> transpozycja_grafu[MAX_N];
vector <bool> visited(MAX_N);

vector <int> kolejnosc;
vector <int> numer_silnie_spojnej_skladowej(MAX_N);
vector <int> silnie_spojne_skladowe[MAX_N];

int kolor;

void DFS(int v)
{
	visited[v] = true;

	for(auto& sasiad : graf[v])
	{
		if(!visited[sasiad])
		{
			DFS(sasiad);
		}
	}

	kolejnosc.push_back(v);
}

void SCC(int v)
{
	visited[v] = true;

	numer_silnie_spojnej_skladowej[v] = kolor;

	for(auto& sasiad : transpozycja_grafu[v])
	{
		if(numer_silnie_spojnej_skladowej[sasiad] == 0)
		{
			SCC(sasiad);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		transpozycja_grafu[b].push_back(a);
	}

	for(int i = 1; i <= n; i++)
	{
		if(!visited[i])
		{
			DFS(i);
		}
	}

	fill(visited.begin(), visited.end(), false);

	for(int i = (int) kolejnosc.size() - 1; i >= 0; i--)
	{
		if(numer_silnie_spojnej_skladowej[kolejnosc[i]])
		{
			kolor++;

			SCC(kolejnosc[i]);
		}
	}

	for(int i = 1; i <= n; i++)
	{
		silnie_spojne_skladowe[numer_silnie_spojnej_skladowej[i]].push_back(i);
		// cout << "D: " << i << ": " << numer_silnie_spojnej_skladowej[i] << "\n";
	}

	return 0;
}
