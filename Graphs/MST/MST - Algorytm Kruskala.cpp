#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

struct Find_And_Union
{
	vector <int> rodzic = vector <int> (MAX_N);
	vector <int> rozmiar = vector <int> (MAX_N);

	int find_set(int v)
	{
		if(v == rodzic[v])
		{
			return v;
		}

		return rodzic[v] = find_set(rodzic[v]);
	}

	void make_set(int v)
	{
		rodzic[v] = v;
		rozmiar[v] = 1;
	}

	void union_sets(int a, int b)
	{
		a = find_set(a);
		b = find_set(b);

		if(a != b)
		{
			if(rozmiar[a] < rozmiar[b])
			{
				swap(a, b);
			}

			rodzic[b] = a;

			rozmiar[a] += rozmiar[b];
		}
	}

	bool check(int a, int b)
	{
		return find_set(a) == find_set(b);
	}
};

struct Krawedz
{
	int sasiad, waga;
};

struct Cala_Krawedz
{
	int a, b, waga;

	bool operator < (const Cala_Krawedz& inny) const
	{
		return waga < inny.waga;
	}
};

struct MST_Algorytm_Kruskala
{
	Find_And_Union find_and_union;

	int koszt_MST = 0;

	vector <Krawedz> MST[MAX_N];

	void Kruskal(vector <Cala_Krawedz>& krawedzie, int n)
	{
		for(int i = 1; i <= n; i++)
		{
			find_and_union.make_set(i);
		}

		sort(krawedzie.begin(), krawedzie.end());

		for(auto& krawedz : krawedzie)
		{
			int a = krawedz.a;
			int b = krawedz.b;
			int waga = krawedz.waga;

			if(!find_and_union.check(a, b))
			{
				find_and_union.union_sets(a, b);

				koszt_MST += waga;

				MST[a].push_back({b, waga});
				MST[b].push_back({a, waga});
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector <Cala_Krawedz> krawedzie(m);

	for(int i = 0; i < m; i++)
	{
		int a, b, waga;
		cin >> a >> b >> waga;

		krawedzie[i].a = a;
		krawedzie[i].b = b;
		krawedzie[i].waga = waga;
	}

	MST_Algorytm_Kruskala mst;

	mst.Kruskal(krawedzie, n);

	return 0;
}
