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

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	Find_And_Union find_and_union;

	for(int i = 1; i <= n; i++)
	{
		find_and_union.make_set(i);
	}

	int t;
	cin >> t;

	for(int numer_zapytania = 0; numer_zapytania < t; numer_zapytania++)
	{
		int operacja, a, b;
		cin >> operacja >> a >> b;

		// znajdz reprezentantow zbiorow, do ktorych naleza a i b
		if(operacja == 0)
		{
			int reprezentant_a = find_and_union.find_set(a);
			int reprezentant_b = find_and_union.find_set(b);

			cout << reprezentant_a << " " << reprezentant_b << "\n";
		}

		// polacz zbiory, do ktorych naleza a i b
		if(operacja == 1)
		{
			find_and_union.union_sets(a, b);
		}

		// sprawdz czy a i b naleza do tego samego zbioru
		if(operacja == 2)
		{
			if(find_and_union.check(a, b))
			{
				cout << "TAK\n";
			}

			else
			{
				cout << "NIE\n";
			}
		}
	}

	return 0;
}
