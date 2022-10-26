#include <bits/stdc++.h>
using namespace std;

// Zlozonosc: O(sqrt(n))

int phi(int n)
{
	int wynik = n;

	for(int i = 2; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			while(n % i == 0)
			{
				n /= i;
			}

			wynik -= wynik / i;
		}
	}

	if(n > 1)
	{
		wynik -= wynik / n;
	}

	return wynik;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	cout << phi(n) << "\n";
	return 0;
}
