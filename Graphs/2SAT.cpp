#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e4 + 5;

vector <int> graf[2 * MAX_N];
vector <int> transpozycja_grafu[2 * MAX_N];
vector <bool> visited(2 * MAX_N);

vector <int> kolejnosc;
vector <int> numer_silnie_spojnej_skladowej(2 * MAX_N);
vector <int> silnie_spojne_skladowe[2 * MAX_N];

vector <bool> rozwiazanie(MAX_N);

int NOT(int v)
{
	return v ^ 1;
}

// Dla danej wartosci mamy pare wierzcholkow w grafie {(2 * wartosc), (2 * wartosc + 1)},
// Gdzie (2 * wartosc) odpowiada negacji wartosci, a (2 * wartosc + 1) odpowiada wartosci
int policz_indeks_wierzcholka(int v, bool czy_negacja)
{
	bool czy_niezanegowana_wartosc = false;

	if(v % 2 == 0)
	{
		czy_niezanegowana_wartosc = true;
	}

	v /= 2;

	v++;

	v *= 2;

	if(czy_niezanegowana_wartosc)
	{
		v = NOT(v);
	}

	if(czy_negacja)
	{
		v = NOT(v);
	}

	return v;
}

void dodaj_klauzule(int a, bool czy_negacja_a, int b, bool czy_negacja_b)
{
	a = policz_indeks_wierzcholka(a, czy_negacja_a);
	b = policz_indeks_wierzcholka(b, czy_negacja_b);

	graf[NOT(a)].push_back(b);
	graf[NOT(b)].push_back(a);

	transpozycja_grafu[b].push_back(NOT(a));
	transpozycja_grafu[a].push_back(NOT(b));
}

void dodaj_implikacje(int a, bool czy_negacja_a, int b, bool czy_negacja_b)
{
	a = policz_indeks_wierzcholka(a, czy_negacja_a);
	b = policz_indeks_wierzcholka(b, czy_negacja_b);

	graf[a].push_back(b);
	graf[NOT(b)].push_back(NOT(a));

	transpozycja_grafu[b].push_back(a);
	transpozycja_grafu[NOT(a)].push_back(NOT(b));
}

void ustaw_true(int v)
{
	dodaj_klauzule(v, false, v, false);
}

void ustaw_false(int v)
{
	dodaj_klauzule(v, true, v, true);
}

void dodaj_OR(int a, int b)
{
	dodaj_klauzule(a, false, b, false);
}

void dodaj_NAND(int a, int b)
{
	dodaj_klauzule(a, true, b, true);
}

// to jest rownoznaczne z <=>, rowniez ==
void dodaj_XNOR(int a, int b)
{
	dodaj_implikacje(a, true, b, true);
	dodaj_implikacje(b, true, a, true);
}

void dodaj_AND(int a, int b)
{
	dodaj_OR(a, b);

	dodaj_XNOR(a, b);
}

void dodaj_NOR(int a, int b)
{
	dodaj_NAND(a, b);

	dodaj_XNOR(a, b);
}

// tez odpowiada !=
void dodaj_XOR(int a, int b)
{
	dodaj_OR(a, b);

	dodaj_NAND(a, b);
}

void DFS(int v)
{
	visited[v] = true;

	for(auto& sasiad : graf[v])
	{
		if(!visited[sasiad])
		{
			DFS(sasiad);
		}
	}

	kolejnosc.push_back(v);
}

void DFS_SCC(int v, int kolor)
{
	visited[v] = true;

	numer_silnie_spojnej_skladowej[v] = kolor;

	for(auto& sasiad : transpozycja_grafu[v])
	{
		if(!visited[sasiad])
		{
			DFS_SCC(sasiad, kolor);
		}
	}
}

bool solve_2SAT(int n)
{
	for(int i = 2; i <= 2 * n + 1; i++)
	{
		if(!visited[i])
		{
			DFS(i);
		}
	}

	fill(visited.begin(), visited.end(), false);

	int kolor = 0;

	for(int i = (int) kolejnosc.size() - 1; i >= 0; i--)
	{
		if(!visited[kolejnosc[i]])
		{
			kolor++;

			DFS_SCC(kolejnosc[i], kolor);
		}
	}

	for(int i = 1; i <= n; i++)
	{
		// rozwiazanie nie istnieje jesli v i !v są w tej samej SCC
		if(numer_silnie_spojnej_skladowej[2 * i] == numer_silnie_spojnej_skladowej[2 * i + 1])
		{
			return false;
		}

		rozwiazanie[i] = (numer_silnie_spojnej_skladowej[2 * i + 1] > numer_silnie_spojnej_skladowej[2 * i]);
	}

	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		dodaj_OR(a, b);
	}

	if(solve_2SAT(n))
	{
		cout << "TAK\n";
	}

	else
	{
		cout << "NIE\n";
	}

	return 0;
}