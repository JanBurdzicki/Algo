#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

struct Krawedz
{
	int sasiad, waga;
};

vector <Krawedz> graf[MAX_N];

vector <int> preorder(MAX_N);
vector <int> postorder(MAX_N);

int timer;

void DFS(int v, int poprzednik)
{
	timer++;

	preorder[v] = timer;

	for(auto& krawedz : graf[v])
	{
		int sasiad = krawedz.sasiad;

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
		int a, b, waga;
		cin >> a >> b >> waga;

		graf[a].push_back({b, waga});
		graf[b].push_back({a, waga});
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