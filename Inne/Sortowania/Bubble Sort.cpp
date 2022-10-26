#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector <int>& liczby, int n)
{
	bool czy_zamienione;

	for(int i = 0; i < n - 1; i++)
	{
		czy_zamienione = false;

		for(int j = 0; j < n - i - 1; j++)
		{
			if(liczby[j] > liczby[j + 1])
			{
				swap(liczby[j], liczby[j + 1]);

				czy_zamienione = true;
			}
		}

		if(!czy_zamienione)
		{
			break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <int> liczby(n);

	for(int i = 0; i < n; i++)
	{
		cin >> liczby[i];
	}

	bubble_sort(liczby, n);

	return 0;
}