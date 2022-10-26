#include <bits/stdc++.h>
using namespace std;

struct Punkt
{
	long long x, y;

	Punkt operator + (const Punkt& inny) const
	{
		return Punkt {x + inny.x, y + inny.y};
	}

	Punkt operator - (const Punkt& inny) const
	{
		return Punkt {x - inny.x, y - inny.y};
	}

	long long cross(const Punkt& inny) const
	{
		return x * inny.y - y * inny.x;
	}

	Punkt() {}

	Punkt(long long _x, long long _y) : x(_x), y(_y) {}

	long long dot(const Punkt& inny) const
	{
		return x * inny.x + y * inny.y;
	}

	long long cross(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).cross(b - *this);
	}

	long long dot(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).dot(b - *this);
	}

	long long sqrLen() const
	{
		return this->dot(*this);
	}
};

// ! Liczenie Sumy Minkowskiego

void reorder_polygon(vector <Punkt>& punkty)
{
	int pozycja = 0;

	for(int i = 1; i < (int) punkty.size(); i++)
	{
		if(punkty[i].y < punkty[pozycja].y || (punkty[i].y == punkty[pozycja].y && punkty[i].x < punkty[pozycja].x))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());
}

// ! Sprawdzanie Czy Punkt Lezy w Wielokacie Wypuklym

bool lexComp(const Punkt& L, const Punkt& R)
{
	return L.x < R.x || (L.x == R.x && L.y < R.y);
}

int sgn(long long val)
{
	return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

vector <Punkt> seq;

int n;
Punkt translation;

bool punkt_w_trojkacie(Punkt a, Punkt b, Punkt c, Punkt punkt)
{
	long long s1 = abs(a.cross(b, c));
	long long s2 = abs(punkt.cross(a, b)) + abs(punkt.cross(b, c)) + abs(punkt.cross(c, a));

	return s1 == s2;
}

void prepare(vector <Punkt>& punkty)
{
	n = (int) punkty.size();
	int pozycja = 0;

	for(int i = 1; i < n; i++)
	{
		if(lexComp(punkty[i], punkty[pozycja]))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());

	n--;

	seq.resize(n);

	for(int i = 0; i < n; i++)
	{
		seq[i] = punkty[i + 1] - punkty[0];
	}

	translation = punkty[0];
}

bool punkt_w_wielokacie_wypuklym(Punkt punkt)
{
	punkt = punkt - translation;

	if(seq[0].cross(punkt) != 0 && sgn(seq[0].cross(punkt)) != sgn(seq[0].cross(seq[n - 1])))
	{
		return false;
	}

	if(seq[n - 1].cross(punkt) != 0 && sgn(seq[n - 1].cross(punkt)) != sgn(seq[n - 1].cross(seq[0])))
	{
		return false;
	}

	if(seq[0].cross(punkt) == 0)
	{
		return seq[0].sqrLen() >= punkt.sqrLen();
	}

	int L = 0, R = n - 1;

	while(R - L > 1)
	{
		int mid = (L + R) / 2;

		if(seq[mid].cross(punkt) >= 0)
		{
			L = mid;
		}

		else
		{
			R = mid;
		}
	}

	int pozycja = L;

	return punkt_w_trojkacie(seq[pozycja], seq[pozycja + 1], Punkt(0, 0), punkt);
}

bool cmp(Punkt a, Punkt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(Punkt a, Punkt b, Punkt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(Punkt a, Punkt b, Punkt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<Punkt>& a) {
    if ((int) a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    Punkt p1 = a[0], p2 = a.back();
    vector<Punkt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int) a.size(); i++) {
        if (i == (int) a.size() - 1 || cw(p1, a[i], p2)) {
            while ((int) up.size() >= 2 && !cw(up[(int) up.size()-2], up[(int) up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == (int) a.size() - 1 || ccw(p1, a[i], p2)) {
            while((int) down.size() >= 2 && !ccw(down[(int) down.size()-2], down[(int) down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int) up.size(); i++)
        a.push_back(up[i]);
    for (int i = (int) down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	// int n;
	cin >> n;

	vector <Punkt> punkty(n);

	for(int i = 0; i < n; i++)
	{
		cin >> punkty[i].x >> punkty[i].y;
	}

	convex_hull(punkty);

	prepare(punkty);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		Punkt zapytanie;
		cin >> zapytanie.x >> zapytanie.y;

		if(punkt_w_wielokacie_wypuklym(zapytanie))
		{
			cout << "TAK\n";
		}

		else
		{
			cout << "NIE\n";
		}
	}

	return 0;
}

// TODO: poprawic wielokat wypukly
// TODO: zrobic wieczorkiem template calosciowy geo, zapytac sie co powinienem miec, co sie wgl pojawia
// TODO: zapytac sie jak sa tresci zadan ukladane





#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2;

struct Punkt
{
	long long x, y;

	Punkt operator + (const Punkt& inny) const
	{
		return Punkt {x + inny.x, y + inny.y};
	}

	Punkt operator - (const Punkt& inny) const
	{
		return Punkt {x - inny.x, y - inny.y};
	}

	Punkt operator * (const long long& inny) const
	{
		return Punkt {inny * x, inny * y};
	}

	long long cross(const Punkt& inny) const
	{
		return x * inny.y - y * inny.x;
	}

	Punkt() {}

	Punkt(long long _x, long long _y) : x(_x), y(_y) {}

	long long dot(const Punkt& inny) const
	{
		return x * inny.x + y * inny.y;
	}

	long long cross(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).cross(b - *this);
	}

	long long dot(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).dot(b - *this);
	}

	long long sqrLen() const
	{
		return this->dot(*this);
	}
};

// ! Liczenie Sumy Minkowskiego

void reorder_polygon(vector <Punkt>& punkty)
{
	int pozycja = 0;

	for(int i = 1; i < (int) punkty.size(); i++)
	{
		if(punkty[i].y < punkty[pozycja].y || (punkty[i].y == punkty[pozycja].y && punkty[i].x < punkty[pozycja].x))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());
}

vector <Punkt> Suma_Minkowskiego(vector <Punkt>& wielokat_1, vector <Punkt>& wielokat_2)
{
	// pierwszy wierzcholek to musi byc najnizszy i najbardziej na lewo

	reorder_polygon(wielokat_1);
	reorder_polygon(wielokat_2);

	// musimy miec cyklicznosc indeskow

	wielokat_1.push_back(wielokat_1[0]);
	wielokat_1.push_back(wielokat_1[1]);
	wielokat_2.push_back(wielokat_2[0]);
	wielokat_2.push_back(wielokat_2[1]);

	vector <Punkt> wynikowy_wielokat;

	int wskaznik_na_wielokat_1 = 0;
	int wskaznik_na_wielokat_2 = 0;

	while(wskaznik_na_wielokat_1 < (int) wielokat_1.size() - 2 || wskaznik_na_wielokat_2 < (int) wielokat_2.size() - 2)
	{
		wynikowy_wielokat.push_back(wielokat_1[wskaznik_na_wielokat_1] + wielokat_2[wskaznik_na_wielokat_2]);

		auto cross = (wielokat_1[wskaznik_na_wielokat_1 + 1] - wielokat_1[wskaznik_na_wielokat_1]).cross(wielokat_2[wskaznik_na_wielokat_2 + 1] - wielokat_2[wskaznik_na_wielokat_2]);

		if(cross >= 0)
		{
			wskaznik_na_wielokat_1++;
		}

		if(cross <= 0)
		{
			wskaznik_na_wielokat_2++;
		}
	}

	return wynikowy_wielokat;
}

// ! Sprawdzanie Czy Punkt Lezy w Wielokacie Wypuklym

bool lexComp(const Punkt& L, const Punkt& R)
{
	return L.x < R.x || (L.x == R.x && L.y < R.y);
}

int sgn(long long val)
{
	return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

vector <Punkt> seq;

int n;
Punkt translation;

bool punkt_w_trojkacie(Punkt a, Punkt b, Punkt c, Punkt punkt)
{
	long long s1 = abs(a.cross(b, c));
	long long s2 = abs(punkt.cross(a, b)) + abs(punkt.cross(b, c)) + abs(punkt.cross(c, a));

	return s1 == s2;
}

void prepare(vector <Punkt>& punkty)
{
	n = (int) punkty.size();
	int pozycja = 0;

	for(int i = 1; i < n; i++)
	{
		if(lexComp(punkty[i], punkty[pozycja]))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());

	n--;
	seq.resize(n);

	for(int i = 0; i < n; i++)
	{
		seq[i] = punkty[i + 1] - punkty[0];
	}

	translation = punkty[0];
}

bool punkt_w_wielokacie_wypuklym(Punkt punkt)
{
	punkt = punkt - translation;

	if(seq[0].cross(punkt) != 0 && sgn(seq[0].cross(punkt)) != sgn(seq[0].cross(seq[n - 1])))
	{
		return false;
	}

	if(seq[n - 1].cross(punkt) != 0 && sgn(seq[n - 1].cross(punkt)) != sgn(seq[n - 1].cross(seq[0])))
	{
		return false;
	}

	if(seq[0].cross(punkt) == 0)
	{
		return seq[0].sqrLen() >= punkt.sqrLen();
	}

	int L = 0, R = n - 1;

	while(R - L > 1)
	{
		int mid = (L + R) / 2;

		if(seq[mid].cross(punkt) >= 0)
		{
			L = mid;
		}

		else
		{
			R = mid;
		}
	}

	int pozycja = L;

	return punkt_w_trojkacie(seq[pozycja], seq[pozycja + 1], Punkt(0, 0), punkt);
}









#include <bits/stdc++.h>
using namespace std;

// TODO: dodac opis i zmienic nazwy, ulepszyc templaty i dodac do biblioteczki

const int MAX_N = 3;

struct Punkt
{
	long long x, y;

	Punkt operator + (const Punkt& inny) const
	{
		return Punkt {x + inny.x, y + inny.y};
	}

	Punkt operator - (const Punkt& inny) const
	{
		return Punkt {x - inny.x, y - inny.y};
	}

	long long cross(const Punkt& inny) const
	{
		return x * inny.y - y * inny.x;
	}

	Punkt() {}

	Punkt(long long _x, long long _y) : x(_x), y(_y) {}

	long long dot(const Punkt& inny) const
	{
		return x * inny.x + y * inny.y;
	}

	long long cross(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).cross(b - *this);
	}

	long long dot(const Punkt& a, const Punkt& b) const
	{
		return (a - *this).dot(b - *this);
	}

	long long sqrLen() const
	{
		return this->dot(*this);
	}
};

// ! Liczenie Sumy Minkowskiego

void reorder_polygon(vector <Punkt>& punkty)
{
	int pozycja = 0;

	for(int i = 1; i < (int) punkty.size(); i++)
	{
		if(punkty[i].y < punkty[pozycja].y || (punkty[i].y == punkty[pozycja].y && punkty[i].x < punkty[pozycja].x))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());
}

vector <Punkt> Suma_Minkowskiego(vector <Punkt>& wielokat_1, vector <Punkt>& wielokat_2)
{
	// pierwszy wierzcholek to musi byc najnizszy i najbardziej na lewo

	reorder_polygon(wielokat_1);
	reorder_polygon(wielokat_2);

	// musimy miec cyklicznosc indeskow

	wielokat_1.push_back(wielokat_1[0]);
	wielokat_1.push_back(wielokat_1[1]);
	wielokat_2.push_back(wielokat_2[0]);
	wielokat_2.push_back(wielokat_2[1]);

	vector <Punkt> wynikowy_wielokat;

	int wskaznik_na_wielokat_1 = 0;
	int wskaznik_na_wielokat_2 = 0;

	while(wskaznik_na_wielokat_1 < (int) wielokat_1.size() - 2 || wskaznik_na_wielokat_2 < (int) wielokat_2.size() - 2)
	{
		wynikowy_wielokat.push_back(wielokat_1[wskaznik_na_wielokat_1] + wielokat_2[wskaznik_na_wielokat_2]);

		auto cross = (wielokat_1[wskaznik_na_wielokat_1 + 1] - wielokat_1[wskaznik_na_wielokat_1]).cross(wielokat_2[wskaznik_na_wielokat_2 + 1] - wielokat_2[wskaznik_na_wielokat_2]);

		if(cross >= 0)
		{
			wskaznik_na_wielokat_1++;
		}

		if(cross <= 0)
		{
			wskaznik_na_wielokat_2++;
		}
	}

	return wynikowy_wielokat;
}

// ! Sprawdzanie Czy Punkt Lezy w Wielokacie Wypuklym

bool lexComp(const Punkt& L, const Punkt& R)
{
	return L.x < R.x || (L.x == R.x && L.y < R.y);
}

int sgn(long long val)
{
	return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

vector <Punkt> seq;

int n;
Punkt translation;

bool punkt_w_trojkacie(Punkt a, Punkt b, Punkt c, Punkt punkt)
{
	long long s1 = abs(a.cross(b, c));
	long long s2 = abs(punkt.cross(a, b)) + abs(punkt.cross(b, c)) + abs(punkt.cross(c, a));

	return s1 == s2;
}

void prepare(vector <Punkt>& punkty)
{
	n = (int) punkty.size();
	int pozycja = 0;

	for(int i = 1; i < n; i++)
	{
		if(lexComp(punkty[i], punkty[pozycja]))
		{
			pozycja = i;
		}
	}

	rotate(punkty.begin(), punkty.begin() + pozycja, punkty.end());

	n--;
	seq.resize(n);

	for(int i = 0; i < n; i++)
	{
		seq[i] = punkty[i + 1] - punkty[0];
	}

	translation = punkty[0];
}

bool punkt_w_wielokacie_wypuklym(Punkt punkt)
{
	punkt = punkt - translation;

	if(seq[0].cross(punkt) != 0 && sgn(seq[0].cross(punkt)) != sgn(seq[0].cross(seq[n - 1])))
	{
		return false;
	}

	if(seq[n - 1].cross(punkt) != 0 && sgn(seq[n - 1].cross(punkt)) != sgn(seq[n - 1].cross(seq[0])))
	{
		return false;
	}

	if(seq[0].cross(punkt) == 0)
	{
		return seq[0].sqrLen() >= punkt.sqrLen();
	}

	int L = 0, R = n - 1;

	while(R - L > 1)
	{
		int mid = (L + R) / 2;

		if(seq[mid].cross(punkt) >= 0)
		{
			L = mid;
		}

		else
		{
			R = mid;
		}
	}

	int pozycja = L;

	return punkt_w_trojkacie(seq[pozycja], seq[pozycja + 1], Punkt(0, 0), punkt);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	vector <Punkt> wielokaty[MAX_N];

	for(int numer_wielokatu = 0; numer_wielokatu < MAX_N; numer_wielokatu++)
	{
		int ilosc_punktow;
		cin >> ilosc_punktow;

		wielokaty[numer_wielokatu].resize(ilosc_punktow);

		for(int i = 0; i < ilosc_punktow; i++)
		{
			cin >> wielokaty[numer_wielokatu][i].x >> wielokaty[numer_wielokatu][i].y;
		}
	}

	vector <Punkt> suma_Minkowskiego_wielokatow;

	suma_Minkowskiego_wielokatow = Suma_Minkowskiego(wielokaty[0], wielokaty[1]);

	suma_Minkowskiego_wielokatow = Suma_Minkowskiego(suma_Minkowskiego_wielokatow, wielokaty[2]);

	int t;
	cin >> t;

	prepare(suma_Minkowskiego_wielokatow);

	for(int i = 0; i < t; i++)
	{
		Punkt zapytanie;
		cin >> zapytanie.x >> zapytanie.y;

		zapytanie.x *= 3;
		zapytanie.y *= 3;

		if(punkt_w_wielokacie_wypuklym(zapytanie))
		{
			cout << "TAK\n";
		}

		else
		{
			cout << "NIE\n";
		}
	}

	return 0;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	vector <Punkt> wielokaty[MAX_N];

	for(int numer_wielokatu = 0; numer_wielokatu < MAX_N; numer_wielokatu++)
	{
		int ilosc_punktow;
		cin >> ilosc_punktow;

		wielokaty[numer_wielokatu].resize(ilosc_punktow);

		for(int i = 0; i < ilosc_punktow; i++)
		{
			cin >> wielokaty[numer_wielokatu][i].x >> wielokaty[numer_wielokatu][i].y;
		}
	}

	vector <Punkt> suma_Minkowskiego_wielokatow;

	suma_Minkowskiego_wielokatow = Suma_Minkowskiego(wielokaty[0], wielokaty[1]);

	suma_Minkowskiego_wielokatow = Suma_Minkowskiego(suma_Minkowskiego_wielokatow, wielokaty[2]);

	int t;
	cin >> t;

	prepare(suma_Minkowskiego_wielokatow);

	for(int i = 0; i < t; i++)
	{
		Punkt zapytanie;
		cin >> zapytanie.x >> zapytanie.y;

		zapytanie.x *= 3;
		zapytanie.y *= 3;

		if(punkt_w_wielokacie_wypuklym(zapytanie))
		{
			cout << "YES\n";
		}

		else
		{
			cout << "NO\n";
		}
	}

	return 0;
}