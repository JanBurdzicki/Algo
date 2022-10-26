#include <bits/stdc++.h>
using namespace std;

struct Treap
{
	int key, priority, rozmiar;
	Treap *L, *R;

	Treap(int _key) : key(_key), priority(rand()), rozmiar(1), L(NULL), R(NULL) {}
};

// TODO: update() -> tego nie jestem pewny -> przetestowac!
void update(Treap* treap)
{
	if(treap == NULL)
	{
		return;
	}

	treap->rozmiar = 1;

	if(treap->L != NULL)
	{
		treap->rozmiar += treap->L->rozmiar;
	}

	if(treap->R != NULL)
	{
		treap->rozmiar += treap->R->rozmiar;
	}
}

// Dzielimy Treapa na L i R wzgledem key -> O(log N)
void split(Treap* treap, int key, Treap*& L, Treap*& R)
{
	if(treap == NULL)
	{
		L = NULL;
		R = NULL;
	}

	else
	{
		if(treap->key <= key)
		{
			split(treap->R, key, treap->R, R);

			L = treap;
		}

		else
		{
			split(treap->L, key, L, treap->L);

			R = treap;
		}
	}

	// Potrzebne jesli chcemy miec aktualne info o poddrzewie
	update(treap);
}

// Wstawienie elementu -> O(log N)
// * split() i 2 merge() -> splitujemy Treapa po key, nastepnie mergujemy L i R z nowym wierzcholkiem
// * schodzimy w glab Treapa do momentu, kiedy priority jest mniejsze od element->priority
// (standardowo jak w zwyklym BST), nastepnie splitujemy Treapa, wtedy L i R beda dziecmi nowego wierzcholka
void insert(Treap*& treap, Treap* element)
{
	if(treap == NULL)
	{
		treap = element;
	}

	else
	{
		if(element->priority > treap->priority)
		{
			split(treap, element->key, element->L, element->R);

			treap = element;
		}

		else
		{
			if(treap->key <= element->key)
			{
				insert(treap->R, element);
			}

			else
			{
				insert(treap->L, element);
			}
		}
	}

	// Potrzebne jesli chcemy miec aktualne info o poddrzewie
	update(treap);
}

// Polaczenie 2 poddrzew -> O(log N)
// * merge(treap_1, treap_2) dziala tylko wtedy, gdy wszystkie key w treap_1 sa mniejsze od wszystkich key w treap_2
// A wiec wybieramy tego Treapa, ktorego priority w korzeniu jest wieksze i do niego podlaczamy drugiego
void merge(Treap*& treap, Treap* L, Treap* R)
{
	if(L == NULL || R == NULL)
	{
		if(L != NULL)
		{
			treap = L;
		}

		else
		{
			treap = R;
		}
	}

	else
	{
		if(L->priority > R->priority)
		{
			merge(L->R, L->R, R);

			treap = L;
		}

		else
		{
			merge(R->L, L, R->L);

			treap = R;
		}
	}

	// Potrzebne jesli chcemy miec aktualne info o poddrzewie
	update(treap);
}

// Usuniecie elementu -> O(log N)
// * 2 split() i merge() -> splitujemy wierzcholek z Treapa, tworzac nowe Treapy L i R,
// nastepnie mergujemy je w nowego Treapa
// * schodzimy w glab Treapa do momentu, szukajac elementu do usuniecia (standardowo jak w zwyklym BST),
// nastepnie mergujemy dzieci wierzcholka w nowego Treapa
void erase(Treap*& treap, int key)
{
	if(treap->key == key)
	{
		Treap* treap_pomocniczy = treap;

		merge(treap, treap->L, treap->R);

		delete treap_pomocniczy;
	}

	else
	{
		if(key < treap->key)
		{
			erase(treap->L, key);
		}

		else
		{
			erase(treap->R, key);
		}
	}

	// Potrzebne jesli chcemy miec aktualne info o poddrzewie
	update(treap);
}

// Polaczenie 2 Treapow -> Teoretyczna zlozonoscia jest O(M log (N / M)), ale w praktyce dziala to bardzo dobrze (prawdopodobnie z bardzo mala ukryta stala)
// * unite(treap_1, treap_2) dziala tylko wtedy, ... TODO:
// TODO: tego nie jestem pewny, sprawdzic -> gdy wszystkie key w treap_1 sa mniejsze od wszystkich key w treap_2
// A wiec wybieramy tego Treapa, ktorego priority w korzeniu jest wieksze i do niego podlaczamy drugiego
Treap* unite(Treap* L, Treap* R)
{
	if(L == NULL || R == NULL)
	{
		if(L != NULL)
		{
			return L;
		}

		else
		{
			return R;
		}
	}

	else
	{
		if(L->priority < R->priority)
		{
			swap(L, R);
		}

		Treap* L_pomocnicze;
		Treap* R_pomocnicze;

		split(R, L->key, L_pomocnicze, R_pomocnicze);

		L->L = unite(L->L, L_pomocnicze);
		L->R = unite(L->R, R_pomocnicze);

		return L;
	}
}

// Budowanie Treapa z listy wartosci
// * O(N log N) -> robimy N insertow wartosci
// * O(N) -> wartosci w liscie musza byc posortowane, TODO: dodac opis jak to sie robi
void build(Treap*& treap, vector <int>& liczby)
{
	for(auto& x : liczby)
	{
		insert(treap, new Treap(x));
	}
}

// Wyswietlamy Treapa w kolejnosci Inorder -> O(N)
void wyswietl_treapa(Treap* treap)
{
	if(treap == NULL)
	{
		return;
	}

	wyswietl_treapa(treap->L);

	cout << treap->key << " ";

	wyswietl_treapa(treap->R);
}

// void test_split(Treap* treap)
// {
// 	Treap* L = NULL;
// 	Treap* R = NULL;

// 	split(treap, 5, L, R);

// 	if(L != NULL)
// 	{
// 		cout << "Rozmiar lewego poddrzewa: " << L->rozmiar << "\n";
// 	}

// 	else
// 	{
// 		cout << "Lewe poddrzewo nie istnieje!\n";
// 	}

// 	if(R != NULL)
// 	{
// 		cout << "Rozmiar prawego poddrzewa: " << R->rozmiar << "\n";
// 	}

// 	else
// 	{
// 		cout << "Prawe poddrzewo nie istnieje!\n";
// 	}
// }

// TODO: pomyslec
	/* remember to add: srand(time(NULL)); in main.cpp */
/*
	inline int Randint()
	{
		return rand(); //Ignore this.
	}

	inline int Randint(int a, int b)
	{
		return a + rand() % (b-a+1);
	}

*/

// TODO: dodac find(), kth(), moze cos jeszcze w stylu policz_indeks()

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

	Treap* treap;

	build(treap, liczby);

	return 0;
}
