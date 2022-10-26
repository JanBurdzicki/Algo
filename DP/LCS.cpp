#include <bits/stdc++.h>
using namespace std;

void LCS(string& s_1, string& s_2)
{
	// Liczenie LCSa

	int rozmiar_1 = (int) s_1.size();
	int rozmiar_2 = (int) s_2.size();

	vector <vector <int>> dp(rozmiar_1 + 1, vector <int> (rozmiar_2 + 1));

	for(int i = 1; i <= rozmiar_1; i++)
	{
		for(int j = 1; j <= rozmiar_2; j++)
		{
			if(s_1[i - 1] == s_2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}

			else
			{
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}

	// dlugosc LCSa jest w dp[rozmiar_1][rozmiar_2]

	cout << dp[rozmiar_1][rozmiar_2] << "\n";

	// Odsyskiwanie LCSa

	string lcs = "";

	for(int i = rozmiar_1, j = rozmiar_2; i > 0 && j > 0; )
	{
		if(s_1[i - 1] == s_2[j - 1])
		{
			// dodajemy literke na poczatek, poniewaz idziemy od konca do poczatku LCSa

			lcs = s_1[i - 1] + lcs;

			i--;
			j--;
		}

		else
		{
			if(dp[i][j - 1] > dp[i - 1][j])
			{
				j--;
			}

			else
			{
				i--;
			}
		}
	}

	cout << lcs << "\n";
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s_1, s_2;
	cin >> s_1 >> s_2;

	LCS(s_1, s_2);

	return 0;
}