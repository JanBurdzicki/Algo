#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;
const int MAX_WYNIK = 1e9 + 5;

// TODO: wersja raczej poprawna, ale nie przetestowana

bool check(int mid)
{
	return false;
}

// Binary_Search po wyniku
int Binary_Search_max()
{
	int L = 0, R = MAX_WYNIK;

	while(L < R)
	{
		int mid = (L + R) / 2;

		if(check(mid))
		{
			R = mid;
		}

		else
		{
			L = mid + 1;
		}
	}

	return R;
}

// Binary_Search po wyniku
int Binary_Search_min()
{
	int L = 0, R = MAX_WYNIK;

	while(L < R)
	{
		int mid = (L + R + 1) / 2;

		if(!check(mid))
		{
			R = mid - 1;
		}

		else
		{
			L = mid;
		}
	}

	return R;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	return 0;
}
