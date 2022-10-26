#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
const double EPSILON = 1e-9;

int Eliminacja_Gaussa(vector <vector <double>>& macierz, vector <int>& odpowiedzi)
{
	int ilosc_wierszy = (int) macierz.size();
	int ilosc_kolumn = (int) macierz[0].size() - 1;

	vector <int> gdzie(ilosc_kolumn, -1);

	int numer_wiersza = 0;
	int numer_kolumny = 0;

	while(numer_wiersza < ilosc_wierszy && numer_kolumny < ilosc_kolumn)
	{
		int wybrany_wiersz = numer_wiersza;

		for(int i = numer_wiersza; i < ilosc_wierszy; i++)
		{
			if(abs(macierz[i][numer_kolumny]) > abs(macierz[wybrany_wiersz][numer_kolumny]))
			{
				wybrany_wiersz = i;
			}
		}

		if(abs(macierz[wybrany_wiersz][numer_kolumny]) < EPSILON)
		{
			numer_kolumny++;

			continue;
		}

		for(int i = numer_kolumny; i <= ilosc_kolumn; i++)
		{
			swap(macierz[wybrany_wiersz][i], macierz[numer_wiersza][i]);
		}

		gdzie[numer_kolumny] = numer_wiersza;

		for(int i = 0; i < ilosc_wierszy; i++)
		{
			if(i != numer_wiersza)
			{
				double wartosc = macierz[i][numer_kolumny] / macierz[numer_wiersza][numer_kolumny];

				for(int j = numer_kolumny; j <= ilosc_kolumn; j++)
				{
					macierz[i][j] -= macierz[numer_wiersza][j] * wartosc;
				}
			}
		}

		numer_wiersza++;
		numer_kolumny++;
	}

	for(int i = 0; i < ilosc_kolumn; i++)
	{
		if(gdzie[i] == -1)
		{
			odpowiedzi[i] = macierz[gdzie[i]][ilosc_kolumn] / macierz[gdzie[i]][i];
		}
	}

	for(int i = 0; i < ilosc_wierszy; i++)
	{
		double suma = 0;

		for(int j = 0; j < ilosc_kolumn; j++)
		{
			suma += odpowiedzi[j] * macierz[i][j];
		}

		if(abs(suma - macierz[i][ilosc_kolumn]) > EPSILON)
		{
			return 0;
		}
	}

	for(int i = 0; i < ilosc_kolumn; i++)
	{
		if(gdzie[i] == -1)
		{
			return INF;
		}
	}

	return 1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);



	return 0;
}
