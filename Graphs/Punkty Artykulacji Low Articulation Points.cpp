#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

vector <int> graf[MAX_N];

vector <bool> visited(MAX_N);

vector <int> preorder(MAX_N);
vector <int> low(MAX_N);

int timer;

void DFS(set <int>& punkty_artykulacji, int v, int poprzednik)
{
	visited[v] = true;

	timer++;

	preorder[v] = timer;

	low[v] = preorder[v];

	int ilosc_dzieci = 0;

	for(auto& sasiad : graf[v])
	{
		if(sasiad == poprzednik)
		{
			continue;
		}

		if(visited[sasiad])
		{
			low[v] = min(low[v], preorder[sasiad]);
		}

		else
		{
			DFS(punkty_artykulacji, sasiad, v);

			low[v] = min(low[v], low[sasiad]);

			if(low[sasiad] >= preorder[v] && poprzednik > 0)
			{
				punkty_artykulacji.insert(v);
			}

			ilosc_dzieci++;
		}
	}

	if(poprzednik == 0 && ilosc_dzieci > 1)
	{
		punkty_artykulacji.insert(v);
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
		graf[b].push_back(a);
	}

	set <int> punkty_artykulacji;

	for(int i = 1; i <= n; i++)
	{
		if(!visited[i])
		{
			DFS(punkty_artykulacji, i, 0);
		}
	}

	cout << (int) punkty_artykulacji.size() << "\n";

	for(auto& punkt_artykulacji : punkty_artykulacji)
	{
		cout << punkt_artykulacji << " ";
	}

	cout << "\n";
	return 0;
}