#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 5;
const int INF = 1e9 + 5;
const int LOG = 19;

struct Krawedz
{
	int sasiad, waga;
};

vector <Krawedz> graf[MAX_N];

vector <int> preorder(MAX_N);
vector <int> postorder(MAX_N);

int up[MAX_N][LOG + 1];
int max_krawedz_LCA[MAX_N][LOG + 1];

int timer;

void DFS(int v, int poprzednik, int poprzednia_waga)
{
	timer++;

	preorder[v] = timer;

	up[v][0] = poprzednik;

	max_krawedz_LCA[v][0] = poprzednia_waga;

	for(int i = 1; i <= LOG; i++)
	{
		up[v][i] = up[up[v][i - 1]][i - 1];

		max_krawedz_LCA[v][i] = max(max_krawedz_LCA[v][i - 1], max_krawedz_LCA[up[v][i - 1]][i - 1]);
	}

	for(auto& krawedz : graf[v])
	{
		int sasiad = krawedz.sasiad;
		int waga = krawedz.waga;

		if(sasiad != poprzednik)
		{
			DFS(sasiad, v, waga);
		}
	}

	timer++;

	postorder[v] = timer;
}

bool is_ancestor(int u, int v)
{
	return preorder[u] <= preorder[v] && postorder[u] >= postorder[v];
}

int policz_LCA(int u, int v)
{
	if(is_ancestor(u, v))
	{
		return u;
	}

	if(is_ancestor(v, u))
	{
		return v;
	}

	for(int i = LOG; i >= 0; i--)
	{
		if(!is_ancestor(up[u][i], v))
		{
			u = up[u][i];
		}
	}

	return up[u][0];
}

int policz_max_krawedz_na_sciezce(int u, int v, int lca)
{
	int max_krawedz_na_sciezce_1 = -INF, max_krawedz_na_sciezce_2 = -INF;

	for(int i = LOG; i >= 0; i--)
	{
		if(!is_ancestor(up[u][i], lca))
		{
			max_krawedz_na_sciezce_1 = max(max_krawedz_na_sciezce_1, max_krawedz_LCA[u][i]);

			u = up[u][i];
		}

		if(!is_ancestor(up[v][i], lca))
		{
			max_krawedz_na_sciezce_2 = max(max_krawedz_na_sciezce_2, max_krawedz_LCA[v][i]);

			v = up[v][i];
		}
	}

	if(up[u][0] == lca)
	{
		max_krawedz_na_sciezce_1 = max(max_krawedz_na_sciezce_1, max_krawedz_LCA[u][0]);
	}

	if(up[v][0] == lca)
	{
		max_krawedz_na_sciezce_2 = max(max_krawedz_na_sciezce_2, max_krawedz_LCA[v][0]);
	}

	int wynik = max(max_krawedz_na_sciezce_1, max_krawedz_na_sciezce_2);

	if(wynik == -INF)
	{
		wynik = 0;
	}

	return wynik;
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

	DFS(1, 1, -INF);

	while(true)
	{
		int a, b;
		cin >> a;

		if(a == -1)
		{
			break;
		}

		cin >> b;

		int lca = policz_LCA(a, b);

		int max_krawedz_na_sciezce = policz_max_krawedz_na_sciezce(a, b, lca);

		cout << max_krawedz_na_sciezce << "\n";
	}

	return 0;
}