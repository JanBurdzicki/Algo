#include <bits/stdc++.h>
using namespace std;

struct Czynnosc
{
    int poczatek, koniec;

    bool operator < (const Czynnosc& inny)
    {
        return koniec < inny.koniec;
    }
};

void Activity_Selection_Problem(vector <Czynnosc>& czynnosci, int n)
{
    sort(czynnosci.begin(), czynnosci.end());

    int ilosc_czynnosci = 1, poprzednia_czynnosc = 0;

    cout << czynnosci[0].poczatek << " " << czynnosci[0].koniec << "\n";

    for(int i = 1; i < n; i++)
    {
        // poczatek i koniec dwoch czynnosci moga sie pokrywac -> znak '>='
        // poczatek i koniec dwoch czynnosci nie moga sie pokrywac -> znak '>'
        if(czynnosci[i].poczatek > czynnosci[poprzednia_czynnosc].koniec)
        {
            cout << czynnosci[i].poczatek << " " << czynnosci[i].koniec << "\n";

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

    vector <Czynnosc> czynnosci(n);

    for(int i = 0; i < n; i++)
    {
        cin >> czynnosci[i].poczatek >> czynnosci[i].koniec;
    }

    Activity_Selection_Problem(czynnosci, n);

    return 0;
}
