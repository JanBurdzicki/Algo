#include <bits/stdc++.h>
using namespace std;

long long policz_max_pole_histogramu(vector <int>& liczby, int n)
{
	stack <int> stos;

	long long max_pole_histogramu = 0;
	long long max_pole_rozwazanego_elementu = 0;
	int wskaznik_na_rozwazany_element = 0;

	int wskaznik_na_liczby = 0;

	while(wskaznik_na_liczby < n)
	{
		if(stos.empty() || liczby[stos.top()] <= liczby[wskaznik_na_liczby])
		{
			stos.push(wskaznik_na_liczby);

			wskaznik_na_liczby++;
		}

		else
		{
			wskaznik_na_rozwazany_element = stos.top();

			stos.pop();

			int dlugosc_przedzialu;

			if(stos.empty())
			{
				dlugosc_przedzialu = wskaznik_na_liczby;
			}

			else
			{
				dlugosc_przedzialu = wskaznik_na_liczby - stos.top() - 1;
			}

			max_pole_rozwazanego_elementu = 1LL * liczby[wskaznik_na_rozwazany_element] * dlugosc_przedzialu;

			max_pole_histogramu = max(max_pole_histogramu, max_pole_rozwazanego_elementu);
		}
	}

	while(!stos.empty())
	{
		wskaznik_na_rozwazany_element = stos.top();

		stos.pop();

		int dlugosc_przedzialu;

		if(stos.empty())
		{
			dlugosc_przedzialu = wskaznik_na_liczby;
		}

		else
		{
			dlugosc_przedzialu = wskaznik_na_liczby - stos.top() - 1;
		}

		max_pole_rozwazanego_elementu = 1LL * liczby[wskaznik_na_rozwazany_element] * dlugosc_przedzialu;

		max_pole_histogramu = max(max_pole_histogramu, max_pole_rozwazanego_elementu);
	}

	return max_pole_histogramu;
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

	long long wynik = policz_max_pole_histogramu(liczby, n);

	cout << wynik << "\n";
	return 0;
}
