#include <bits/stdc++.h>
using namespace std;

// Zlozonosc czasowa: O(dlugosc_napisu * dlugosc_wzorca)
// Zlozonosc pamieciowa: O(dlugosc_napisu)
int policz_odleglosc_edycyjna(string& napis, string& wzorzec, int dlugosc_napisu, int dlugosc_wzorca)
{
	vector <vector <int>> dp(2, vector <int> (dlugosc_napisu + 1));

	// jesli wzorzec jest pustym napisem, to usuwamy wszystkie znaki
	for(int i = 0; i <= dlugosc_napisu; i++)
	{
		dp[0][i] = i;
	}

	// dla kazdego znaku z wzorca
	for(int i = 1; i <= dlugosc_wzorca; i++)
	{
		// porownywanie znaku z wzorca ze znakami napisu
		for(int j = 0; j <= dlugosc_napisu; j++)
		{
			// jesli napis jest pusty, to musimy dodac wszystkie znaki, zeby otrzymac wzorzec
			if(j == 0)
			{
				dp[i % 2][j] = i;
			}

			else
			{
				// jesli znaki w napisie i wzorcu sa takie same, to nie musimy nic dodawac, usuwac i zmieniac
				// czyli pomijamy ten znak i wynik sie nie zmiania
				// i % 2 jest do okreslenia wiersza
				if(napis[j - 1] == wzorzec[i - 1])
				{
					dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
				}

				// jesli znaki w napisie i wzorcu sa rozne, to bierzemy min(dodac, usunac, zmienic)
				// dodac -> dp[i % 2][j - 1]
				// usunac -> dp[(i - 1) % 2][j]
				// zmienic -> dp[(i - 1) % 2][j - 1]
				// i % 2 jest do okreslenia wiersza
				else
				{
					dp[i % 2][j] = min({dp[i % 2][j - 1], dp[(i - 1) % 2][j], dp[(i - 1) % 2][j - 1]}) + 1;
				}
			}
		}
	}

	// po wypelnieniu dp[][]
	// jesli dlugosc_wzorca % 2 == 0, to skonczymy w zerowym wierszu
	// jesli dlugosc_wzorca % 2 == 1, to skonczymy w pierszym wierszu
	// odleglosc edycyjna jest w dp[dlugosc_wzorca % 2][dlugosc_napisu]

	return dp[dlugosc_wzorca % 2][dlugosc_napisu];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int dlugosc_napisu, dlugosc_wzorca;
	cin >> dlugosc_napisu >> dlugosc_wzorca;

	string napis, wzorzec;
	cin >> napis >> wzorzec;

	cout << policz_odleglosc_edycyjna(napis, wzorzec, dlugosc_napisu, dlugosc_wzorca) << "\n";
	return 0;
}
