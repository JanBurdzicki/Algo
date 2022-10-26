#include <bits/stdc++.h>
using namespace std;

// zadanie z IOI 2008 na trie, zadanie na OIG 2015 (IX OIG)

// TODO: chyba chce wiedziec ile slow sie konczy w jakims wierzcholku, poniewaz wtedy int ma wiecej zastosowac niz bool

// Formalnie drzewo trie to drzewo ukorzenione, w ktorym kazda krawedz drzewa jest oznaczona jakas litera
// Wszystkie krawedzie wychodzace z jednego wierzcholka musza miec rozne etykiety

// Rozwazmy dowolna sciezke w drzewie trie od korzenia do dowolnego wierzcholka
// Jesli wypiszemy etykiety wszystkich krawedzi na sciezce, to otrzymamy ciag odpowiadajacy tej sciezce
// Dla dowolnego wierzcholka w trie skojarzymy ciag od korzenia do wierzcholka

// Kazdy wierzcholek bedzie rowniez mial flage czy_lisc, ktora bedzie prawda, jesli temu wierzcholkowi bedzie odpowiadal dowolny ciag z podanego zbioru

// W zwiazku z tym zbudowanie drzewa trie dla zestawu ciagow oznacza zbudowac drzewo trie takie,
// Ze kazdy wierzcholek, ktory jest lisciem bedzie odpowiadal jednemu ciagowi ze zbioru i odwrotnie,
// Kazdy ciag w zbiorze odpowiada jednemu wierzcholkowi, ktory jest lisciem

// Drzewo trie konstruujemy dla danego zbioru ciagow w czasie liniowym od ich calkowitej dlugosci

const int MAX_N = 1e5 + 5;
const int DLUGOSC_ALFABETU = 26;

// TODO: zapytac sie bambusa i marasa czy lepiej robic tablice 2D na wektorze czy na tablicy
int trie[MAX_N][DLUGOSC_ALFABETU];
int ilosc_konczacych_sie_w_wierzcholku[MAX_N];

void dodaj_napis(string const& s)
{
	int ilosc_wierzcholkow = 0;

	int v = 0;

	for(auto& znak : s)
	{
		int sasiad = znak - 'a';

		if(trie[v][sasiad] == 0)
		{
			ilosc_wierzcholkow++;

			trie[v][sasiad] = ilosc_wierzcholkow;
		}

		v = trie[v][sasiad];
	}

	ilosc_konczacych_sie_w_wierzcholku[v]++;
}

bool czy_istnieje(const string& s)
{

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);



	return 0;
}

// Trzymamy sobie wektor wierzcholkow, kazdy wierzcholek zawiera flage czy_lisc i wektor nastepny zawierajacy zbior krawedzi wychodzacych z obecnego wierzcholka
// Dokladniej nastepny[i] oznacza numer wierzcholka, do ktorego przejdziemy idac krawedzia, ktora zawiera znak i
// Lub -1, jesli nie ma takiej krawedzi

// Poczatkowo drzewo trie sklada sie tylko z jednego wierzcholka - korzenia, ktory ma indeks 0

// Funkcja, ktora doda napis s do drzewa trie polega na tym, ze zaczynamy od korzenia i:
// * jesli istnieja krawedzie odpowiadajace znakom s, to podazamy za nimi
// * w przeciwnym przypadku po prostu generujemy nowy wierzcholek i laczymy go krawedzia
// Na koniec procesu zaznaczamy ostatni wierzcholek flaga czy_lisc

// Zlozonosc czasowa: O(TODO:)
// Zlozonosc pamieciowa: O(m * DLUGOSC_ALFABETU), mozemy zmniejszyc zlozonosc pamieciowa do O(m) uzywajac mapy w kazdym wierzcholku zamiast vectora, ale to spowoduje zwiekszenie zlozonosci czasowej do O(n log DLUGOSC_ALFABETU)