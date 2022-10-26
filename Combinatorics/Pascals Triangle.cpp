#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e3 + 5;
const int MOD = 1e9 + 7;

long long binomial_coefficient[MAX_N][MAX_N];

// ! Binomial Coefficient z Trojkata Pascala -> O(n ^ 2)

void policz_Trojkat_Pascala()
{
	binomial_coefficient[0][0] = 1;

	for(int n = 1; n < MAX_N; n++)
	{
		binomial_coefficient[n][0] = 1;
		binomial_coefficient[n][n] = 1;

		for(int k = 1; k < n; k++)
		{
			binomial_coefficient[n][k] = (binomial_coefficient[n - 1][k - 1] + binomial_coefficient[n - 1][k]) % MOD;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	policz_Trojkat_Pascala();

	return 0;
}