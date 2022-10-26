#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

vector <int> graf[MAX_N];

vector <bool> visited(MAX_N);

#warning usunac z pozostalych implementacji postoredera, jest niepotrzebny
vector <int> preorder(MAX_N);
vector <int> low(MAX_N);

// vector <int> parent(MAX_N);

// vector <int> numer_dwuspojnej_skladowej(MAX_N);
vector <vector <int>> dwuspojne_skladowe;

vector <bool> czy_jest_na_stosie(MAX_N);

#warning zastanowic sie czy to ma byc stack czy vector, stack bardziej pokazuje do czego to sluzy, ale zastanowic sie
stack <int> stos;

int timer;

void DFS(int v, int poprzednik)
{
	visited[v] = true;

	stos.push(v);

	czy_jest_na_stosie[v] = true;

	timer++;

	preorder[v] = timer;

	low[v] = preorder[v];

	// int ilosc_dzieci = 0;

	for(auto& sasiad : graf[v])
	{
		if(sasiad == poprzednik)
		{
			continue;
		}

		#warning tutaj nastapila zmiana warunkow, zastanowic sie czy to mi odpowiada, i pozmieniac w pozostalych implementacjach, zeby bylo jednolicie
		// else if dziala jak else + if zagniezdzony
		if(!visited[sasiad])
		{
			// ilosc_dzieci++;

			// parent[sasiad] = v;

			DFS(sasiad, v);

			low[v] = min(low[v], low[sasiad]);
		}

		else if(czy_jest_na_stosie[sasiad])
		{
			low[v] = min(low[v], preorder[sasiad]);
		}
	}

	if(low[v] == preorder[v])
	{
		vector <int> dwuspojna_skladowa;

		while(stos.top() != v)
		{
			// TODO: zastanowic sie czy tak chce, a nie miec w warunku zmiennej, chyba jednak jest dobrze
			int wierzcholek = stos.top();

			dwuspojna_skladowa.push_back(wierzcholek);

			czy_jest_na_stosie[wierzcholek] = false;

			stos.pop();
		}

		int wierzcholek = stos.top();

		dwuspojna_skladowa.push_back(wierzcholek);

		czy_jest_na_stosie[wierzcholek] = false;

		stos.pop();

		dwuspojne_skladowe.push_back(dwuspojna_skladowa);
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

	for(int i = 1; i <= n; i++)
	{
		if(!visited[i])
		{
			DFS(i, 0);
		}
	}

	for(auto& dwuspojna_skladowa : dwuspojne_skladowe)
	{
		cout << "D: ";

		for(auto& v : dwuspojna_skladowa)
		{
			cout << v << " ";
		}

		cout << "\n";
	}

	return 0;
}