#include <bits/stdc++.h>
using namespace std;

const int BASE = 1 << 20;

vector <int> segtree(BASE << 1);
vector <int> lazy(BASE << 1);

void push(int v)
{
	segtree[v] = lazy[v];

	if(v < BASE)
	{
		// mnozymy razy 2
		int lewy_syn = v << 1;

		// mnozymy razy 2 i dodajemy 1
		int prawy_syn = (v << 1) + 1;

		lazy[lewy_syn] = lazy[v];
		lazy[prawy_syn] = lazy[v];
	}

	lazy[v] = 0;
}

void update(int L, int R, int wartosc, int v = 1, int a = 1, int b = BASE)
{
	push(v);

	if(b < L || a > R)
	{
		return;
	}

	if(L <= a && b <= R)
	{
		lazy[v] = wartosc;
		push(v);

		return;
	}

	int mid = (a + b) / 2;

	// mnozymy razy 2
	int lewy_syn = v << 1;

	// mnozymy razy 2 i dodajemy 1
	int prawy_syn = (v << 1) + 1;

	update(L, R, wartosc, lewy_syn, a, mid);
	update(L, R, wartosc, prawy_syn, mid + 1, b);

	segtree[v] = max(segtree[lewy_syn], segtree[prawy_syn]);
}

int query(int L, int R, int v = 1, int a = 1, int b = BASE)
{
	push(v);

	if(b < L || a > R)
	{
		return 0;
	}

	if(L <= a && b <= R)
	{
		return segtree[v];
	}

	int mid = (a + b) / 2;

	// mnozymy razy 2
	int lewy_syn = v << 1;

	// mnozymy razy 2 i dodajemy 1
	int prawy_syn = (v << 1) + 1;

	return max(query(L, R, lewy_syn, a, mid), query(L, R, prawy_syn, mid + 1, b));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int szerokosc, t;
	cin >> szerokosc >> t;

	for(int i = 0; i < t; i++)
	{
		int L, R, dlugosc;
		cin >> dlugosc >> L;

		R = L + dlugosc;
		L++;

		int max_wysokosc = query(L, R);

		update(L, R, max_wysokosc + 1);
	}

	cout <<	query(1, BASE) << "\n";

	return 0;
}