#include <bits/stdc++.h>
using namespace std;

struct Funkcja_Z
{
	vector <int> wartosci_funkcji_z;

	Funkcja_Z(string& s)
	{
		int n = (int) s.size();

		wartosci_funkcji_z.resize(n);

		int L = 0, R = 0;

		for(int i = 1; i < n; i++)
		{
			if(i <= R)
			{
				int dlugosc_przedzialu = R - i + 1;

				wartosci_funkcji_z[i] = min(dlugosc_przedzialu, wartosci_funkcji_z[i - L]);
			}

			while(i + wartosci_funkcji_z[i] < n && s[wartosci_funkcji_z[i]] == s[i + wartosci_funkcji_z[i]])
			{
				wartosci_funkcji_z[i]++;
			}

			if(i + wartosci_funkcji_z[i] - 1 > R)
			{
				L = i;
				R = i + wartosci_funkcji_z[i] - 1;
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	Funkcja_Z funkcja_z(s);

	for(int i = 0; i < (int) s.size(); i++)
	{
		cout << funkcja_z.wartosci_funkcji_z[i] << " ";
	}

	cout << "\n";
	return 0;
}
