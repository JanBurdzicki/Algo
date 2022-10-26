#include <bits/stdc++.h>
using namespace std;

// TODO: nieprzetestowane

const int DLUGOSC_ALFABETU = 26;
const int MAX_N = 2 * DLUGOSC_ALFABETU;

vector <int> ilosci_literek(DLUGOSC_ALFABETU);

vector <int> graf[MAX_N];

map <string, int> mapka;

int numer_indeksu;

struct Stan
{
	string s;
	int ilosc;

	bool operator < (const Stan& inny) const
	{
		return ilosc < inny.ilosc;
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	for(auto& x : s)
	{
		ilosci_literek[x - 'a']++;
	}

	set <Stan> secik;

	for(int i = 0; i < DLUGOSC_ALFABETU; i++)
	{
		if(ilosci_literek[i] > 0)
		{
			string napis = "";

			napis += (char) (i + 'a');

			numer_indeksu++;

			mapka[napis] = numer_indeksu;

			secik.insert({napis, ilosci_literek[i]});
		}
	}

	while((int) secik.size() > 1)
	{
		auto it_1 = secik.begin();

		string s_1 = it_1->s;

		int ilosc_1 = it_1->ilosc;

		secik.erase(it_1);

		auto it_2 = secik.begin();

		string s_2 = it_2->s;

		int ilosc_2 = it_2->ilosc;

		secik.erase(it_2);

		string nowy_s = s_1 + s_2;

		int nowa_ilosc = ilosc_1 + ilosc_2;

		int indeks_1 = mapka[s_1];
		int indeks_2 = mapka[s_2];

		numer_indeksu++;

		mapka[nowy_s] = numer_indeksu;

		graf[numer_indeksu].push_back(indeks_1);
		graf[indeks_1].push_back(numer_indeksu);

		graf[numer_indeksu].push_back(indeks_2);
		graf[indeks_2].push_back(numer_indeksu);

		secik.insert({nowy_s, nowa_ilosc});
	}

	return 0;
}
