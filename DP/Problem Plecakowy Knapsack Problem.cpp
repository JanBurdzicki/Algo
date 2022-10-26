#include <bits/stdc++.h>
using namespace std;

int policz_plecak()
{

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	// vector <vector <int>> dp(n + 1, vector <int> (MAX_SUMA_ILOSCI_RUCHOW));

	// for(int i = 0; i < n; i++)
	// {
	// 	for(int suma_ilosci_ruchow = 0; suma_ilosci_ruchow <= max_ilosc_operacji; suma_ilosci_ruchow++)
	// 	{
	// 		if(suma_ilosci_ruchow + ilosci_ruchow[i] <= max_ilosc_operacji)
	// 		{
	// 			dp[i + 1][suma_ilosci_ruchow + ilosci_ruchow[i]] = max(dp[i + 1][suma_ilosci_ruchow + ilosci_ruchow[i]], dp[i][suma_ilosci_ruchow] + koszty[i]);
	// 		}

	// 		dp[i + 1][suma_ilosci_ruchow] = max(dp[i + 1][suma_ilosci_ruchow], dp[i][suma_ilosci_ruchow]);
	// 	}
	// }

	// cout << dp[n][max_ilosc_operacji] << "\n";

	return 0;
}
