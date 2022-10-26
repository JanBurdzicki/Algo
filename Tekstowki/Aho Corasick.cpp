#include <bits/stdc++.h>
using namespace std;

const int K = 26;

struct Wierzcholek
{
	int next[K];
	bool leaf = false;
	int p = -1;
	char pch;
	int link = -1;
	int go[K];

	Wierzcholek(int p=-1, char ch='$') : p(p), pch(ch)
	{
		fill(begin(next), end(next), -1);
		fill(begin(go), end(go), -1);
	}
};

vector <Wierzcholek> trie(1);

void add_string(string const& s) {
	int v = 0;
	for (char ch : s) {
		int c = ch - 'a';
		if (trie[v].next[c] == -1) {
			trie[v].next[c] = trie.size();
			trie.emplace_back(v, ch);
		}
		v = trie[v].next[c];
	}
	trie[v].leaf = true;
}

int go(int v, char ch);

int get_link(int v) {
	if (trie[v].link == -1) {
		if (v == 0 || trie[v].p == 0)
			trie[v].link = 0;
		else
			trie[v].link = go(get_link(trie[v].p), trie[v].pch);
	}
	return trie[v].link;
}

int go(int v, char ch)
{
	int sasiad = ch - 'a';

	if(trie[v].go[sasiad] == -1)
	{
		if(trie[v].next[sasiad] != -1)
		{
			trie[v].go[sasiad] = trie[v].next[sasiad];
		}

		else
		{
			trie[v].go[sasiad] = v == 0 ? 0 : go(get_link(v), ch);
		}
	}

	return trie[v].go[sasiad];
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);



	return 0;
}
