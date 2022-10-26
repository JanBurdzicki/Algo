#include <bits/stdc++.h>
using namespace std;

vector <int> Centroid(const vector <vector <int>>& graf, int n)
{
	//int n = (int) graf.size();
	vector <int> centroid, sz(n + 1);

	// Znajdujemy te wierzcholki poprzez sprawdzenie rozmiaru kazdego poddrzewa, robiac DFS
	// Jesli rozmiar poddrzewa jest rowny s, to rozmiar pozostalych poddrzew jest rowny n - s

	function <void (int, int)> DFS = [&](int u, int prev)
	{
		sz[u] = 1;
		bool is_centroid = true;

		for(auto v : graf[u])
		{
			if(v != prev)
			{
				DFS(v, u);
				sz[u] += sz[v];

				if(sz[v] > n / 2)
				{
					is_centroid = false;
				}
			}
		}

		if(n - sz[u] > n / 2)
		{
			is_centroid = false;
		}

		if(is_centroid)
		{
			centroid.push_back(u);
		}
	};

	DFS(1, -1);
	return centroid;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int n;
	cin >> n;

	vector <vector <int>> graf(n + 1);

	for(int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;

		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	vector <int> centroid = Centroid(graf, n);

	// Drzewo moze miec 1 lub 2 centroidy
	// Jesli ma 2, to zawsze sa one polaczone (inaczej drzewo nie moze miec n wierzcholkow)

	if((int) centroid.size() == 1)
	{
		int c1 = centroid[0];
	}

	else if((int) centroid.size() == 2)
	{
		int c1 = centroid[0];
		int c2 = centroid[1];
	}

	else
	{
		assert(false);
	}

	return 0;
}
