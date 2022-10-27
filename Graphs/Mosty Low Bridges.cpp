#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

struct Most
{
	int a, b;

	Most(int a, int b)
	{
		if(a > b)
		{
			swap(a, b);
		}

		this->a = a;
		this->b = b;
	}

	bool operator < (const Most& inny) const
	{
		if(a != inny.a)
		{
			return a < inny.a;
		}

		else
		{
			return b < inny.b;
		}
	}
};

vector <int> graf[MAX_N];

vector <bool> visited(MAX_N);

vector <int> preorder(MAX_N);
vector <int> low(MAX_N);

int timer;

void DFS(vector <Most>& mosty, int v, int poprzednik)
{
	visited[v] = true;

	timer++;

	preorder[v] = timer;

	low[v] = preorder[v];

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
			DFS(mosty, sasiad, v);

			low[v] = min(low[v], low[sasiad]);

			if(low[sasiad] > preorder[v])
			{
				mosty.push_back({v, sasiad});
			}
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
		graf[b].push_back(a);
	}

	vector <Most> mosty;

	for(int i = 1; i <= n; i++)
	{
		if(!visited[i])
		{
			DFS(mosty, i, 0);
		}
	}

	sort(mosty.begin(), mosty.end());

	for(auto& most : mosty)
	{
		cout << most.a << " " << most.b << "\n";
	}

	return 0;
}