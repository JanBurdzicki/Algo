#include <bits/stdc++.h>
using namespace std;

// Inne implementacje !!!

// struct Czynnosc
// {
//     int poczatek, koniec;

//     bool operator < (const Czynnosc& inny)
//     {
//         return koniec < inny.koniec;
//     }
// };

void solve(vector <pair <int, int>>& czynnosci, int n)
{
    sort(czynnosci.begin(), czynnosci.end(),
    [&] (const pair <int, int>& x, const pair <int, int>& y)
    {
        return x.second < y.second;
    });

    int ilosc_czynnosci = 1, poprzednia_czynnosc = 0;

    cout << czynnosci[0].first << " " << czynnosci[0].second << "\n";

    for(int i = 1; i < n; i++)
    {
        // poczatek i koniec dwoch czynnosci moga sie pokrywac -> znak '>='
        // poczatek i koniec dwoch czynnosci nie moga sie pokrywac -> znak '>'
        if(czynnosci[i].first > czynnosci[poprzednia_czynnosc].second)
        {
            cout << czynnosci[i].first << " " << czynnosci[i].second << "\n";

            ilosc_czynnosci++;

            poprzednia_czynnosc = i;
        }
    }

    cout << ilosc_czynnosci << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // {poczatek, koniec}
    vector <pair <int, int>> czynnosci(n);

    for(int i = 0; i < n; i++)
    {
        cin >> czynnosci[i].first >> czynnosci[i].second;
    }

    solve(czynnosci, n);

    return 0;
}
