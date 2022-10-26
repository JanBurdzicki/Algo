#include <bits/stdc++.h>
using namespace std;

const int MAX_DLUGOSC = 1e6;

int tab[MAX_DLUGOSC];

void FastI_getchar()
{
	for(int i = 0; i < MAX_DLUGOSC; i++)
	{
		int result = 0;
		char c = '0';

		while(c >= '0')
		{
			result = result * 10 + (c - '0');
			c = getchar();
		}

		tab[i] = result;
	}
}

void FastO_getchar(int x, char odstep)
{
	char tab[12];

	int p = 0;

	while(x)
	{
		tab[p] = (x % 10) + 48;

		p++;

		x /= 10;
	}

	while(p--)
	{
		putc(tab[p], stdout);
		// putc_unlocked(tab[p], stdout);
	}

	putc(odstep, stdout);
	// putc_unlocked(nl, stdout);
}

int main()
{
	int x;
	FastI_getchar();
	FastO_getchar(2 * x, ' ');


	return 0;
}
/*

#include <cstdio>
using namespace std;
constexpr int MxK = 2e6+66, MxN = 1e6+66;
int ans[MxK][2];
char s[MxN];

inline void computesums(int st, int ed, int sum)
{
	while (1)
	{
		ans[sum][0] = st + 1;
		ans[sum][1] = ed + 1;

		if (sum <= 2)
			return;

		if (s[st] == 'T') st++, sum -= 2;
		else if (s[ed] == 'T') ed--, sum -= 2;
		else st++, ed--, sum -= 2;
	}
}

inline int fastINPUT()
{
	int res = 0;
	register char c = '0';
	while (c >= '0')
	{
		res = res * 10 + (c-'0');
		c = getchar_unlocked();
	}
	return res;
}

inline void fastOUTPUT(int x, char nl)
{
	char tab[12];
	register int p = 0;
	while (x)
	{
		tab[p++] = (x % 10) + 48;
		x /= 10;
	}
	while (p--)
		putc_unlocked(tab[p], stdout);
	putc_unlocked(nl, stdout);
}

int main()
{
	int n = fastINPUT();
	int m = fastINPUT();

	for (int i=0; i<=n; i++)
		s[i] = getc_unlocked(stdin);

	int sum = 0;
	for (int i=0; i<n; i++)
		sum += (s[i] == 'T' ? 2 : 1);

	computesums(0, n-1, sum);

	int i = 0, j = n-1;
	while (s[i] == 'T' && s[j] == 'T')
		i++, j--;

	if (s[i] == 'W')
		computesums(i+1, n-1, sum - 2*i-1);
	else
		computesums(0, j-1, sum - 2*(n-1-j)-1);

	for (int i=0; i<m; i++)
	{
		register int k = fastINPUT();
		if (ans[k][0] == 0 && ans[k][1] == 0)
		{
			putc_unlocked('N', stdout);
			putc_unlocked('I', stdout);
			putc_unlocked('E', stdout);
			putc_unlocked('\n', stdout);
		}
		else
		{
			fastOUTPUT(ans[k][0], ' ');
			fastOUTPUT(ans[k][1], '\n');
		}
	}

	return 0;
}


*/