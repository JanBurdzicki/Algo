#include <bits/stdc++.h>
using namespace std;

// TODO: wpakowac to w structa

const int MAX_N = 1e6 + 5;

vector <int> graf[MAX_N];

vector <int> stopien_wchodzacych(MAX_N);
vector <int> topo_sort;

void topological_sort(int n)
{
	queue <int> kolejka;

	for(int i = 1; i <= n; i++)
	{
		if(stopien_wchodzacych[i] == 0)
		{
			kolejka.push(i);
		}
	}

	while(!kolejka.empty())
	{
		int v = kolejka.front();

		topo_sort.push_back(v);

		kolejka.pop();

		for(auto& sasiad : graf[v])
		{
			stopien_wchodzacych[sasiad]--;

			if(stopien_wchodzacych[sasiad] == 0)
			{
				kolejka.push(sasiad);
			}
		}
	}

	if((int) topo_sort.size() != n)
	{
		cout << "JEST CYKL\n";
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

		stopien_wchodzacych[b]++;
	}

	topological_sort(n);

	for(auto& v : topo_sort)
	{
		cout << v << " ";
	}

	cout << "\n";
	return 0;
}
