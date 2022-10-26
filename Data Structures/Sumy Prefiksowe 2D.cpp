#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e3 + 5;

long long sumy_prefiksowe_2D[MAX_N][MAX_N];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			cin >> sumy_prefiksowe_2D[i][j];
		}
	}

	for(int i = 1; i < MAX_N; i++)
	{
		for(int j = 1; j < MAX_N; j++)
		{
			sumy_prefiksowe_2D[i][j] += sumy_prefiksowe_2D[i][j - 1] + sumy_prefiksowe_2D[i - 1][j] - sumy_prefiksowe_2D[i - 1][j - 1];
		}
	}

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		long long prostokat = sumy_prefiksowe_2D[x2][y2] - sumy_prefiksowe_2D[x1 - 1][y2] - sumy_prefiksowe_2D[x2][y1 - 1] + sumy_prefiksowe_2D[x1 - 1][y1 - 1];
	}

	return 0;
}