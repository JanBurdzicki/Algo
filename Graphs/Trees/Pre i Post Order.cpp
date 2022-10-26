#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

vector <int> graf[MAX_N];

vector <int> preorder(MAX_N);
vector <int> postorder(MAX_N);

int timer;

void DFS(int v, int poprzednik)
{
	timer++;

	preorder[v] = timer;

	for(auto& sasiad : graf[v])
	{
		if(sasiad != poprzednik)
		{
			DFS(sasiad, v);
		}
	}

	timer++;

	postorder[v] = timer;
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

		graf[a].push_back({b});
		graf[b].push_back({a});
	}

	DFS(1, 1);

	for(int i = 1; i <= n; i++)
	{
		cout << preorder[i] << " ";
	}

	cout << "\n";

	for(int i = 1; i <= n; i++)
	{
		cout << postorder[i] << " ";
	}

	cout << "\n";
	return 0;
}