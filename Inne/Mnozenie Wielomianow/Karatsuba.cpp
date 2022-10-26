#include <bits/stdc++.h>
using namespace std;

struct Wielomian
{
	vector <int> wielomian;

	// chcemy sie dostac do jakiegos indeksu i go moc zmienic
	int& operator[](int indeks)
	{
		return wielomian[indeks];
	}

	int operator[](int indeks) const
	{
		return wielomian[indeks];
	}

	// piszemy funkcje size(), zeby nam sie przyjemniej korzystalo
	int size() const
	{
		return (int) wielomian.size();
	}

	// piszemy funkcje resize(), zeby nam sie przyjemniej korzystalo
	void resize(int rozmiar)
	{
		return wielomian.resize(rozmiar);
	}

	// piszemy funkcje push_back(), zeby nam sie przyjemniej korzystalo
	void push_back(int wartosc)
	{
		return wielomian.push_back(wartosc);
	}

	// Dzielimy wielomian na polowki
	pair <Wielomian, Wielomian> podziel_wielomian(int pozycja) const
	{
		return {{vector <int> (wielomian.begin(), wielomian.begin() + pozycja)}, {vector <int> (wielomian.begin() + pozycja, wielomian.end())}};
	}

	Wielomian dodaj_zera_na_koncu(int rozmiar) const
	{
		auto rozszerzony_wielomian = *this;

		while(rozszerzony_wielomian.size() < rozmiar)
		{
			rozszerzony_wielomian.push_back(0);
		}

		return rozszerzony_wielomian;
	}

	Wielomian przesun_wielomian(int pozycja) const
	{
		Wielomian przesuniety_wielomian;

		przesuniety_wielomian.resize(pozycja + wielomian.size());

		copy(wielomian.begin(), wielomian.end(), przesuniety_wielomian.wielomian.begin() + pozycja);

		return przesuniety_wielomian;
	}
};

Wielomian operator + (const Wielomian& wielomian_1, const Wielomian& wielomian_2)
{
	if(wielomian_1.size() > wielomian_2.size())
	{
		return wielomian_2 + wielomian_1;
	}

	auto wynik = wielomian_2;

	for(int i = 0; i < wielomian_1.size(); i++)
	{
		wynik[i] += wielomian_1[i];
	}

	return wynik;
}

Wielomian operator - (const Wielomian& wielomian)
{
	auto wynik = wielomian;

	for(auto& x : wynik.wielomian)
	{
		x = -x;
	}

	return wynik;
}

Wielomian operator - (const Wielomian& wielomian_1, const Wielomian& wielomian_2)
{
	return wielomian_1 + (-wielomian_2);
}

Wielomian operator * (const Wielomian& wielomian_1, const Wielomian& wielomian_2)
{
	if(wielomian_1.size() > wielomian_2.size())
	{
		return wielomian_2 * wielomian_1;
	}

	if(wielomian_1.size() < wielomian_2.size())
	{
		return wielomian_1.dodaj_zera_na_koncu(wielomian_2.size()) * wielomian_2;
	}

	// rozmiary sa rowne

	if(wielomian_1.size() < 64) // TODO: wyzylowac tutaj stala 17, 128
	{
		vector <int> wynik(wielomian_1.size() + wielomian_2.size() - 1);

		for(int i = 0; i < wielomian_1.size(); i++)
		{
			for(int j = 0; j < wielomian_2.size(); j++)
			{
				wynik[i + j] += wielomian_1[i] * wielomian_2[j];
			}
		}

		return {wynik};
	}

	const int mid = wielomian_1.size() / 2;

	// TODO: ogarnac jak tutaj mozna zrobic structered binding, bo traktuje to jako funkcje

	Wielomian a_L, a_R;
	tie(a_L, a_R) = wielomian_1.podziel_wielomian(mid);

	Wielomian b_L, b_R;
	tie(b_L, b_R) = wielomian_2.podziel_wielomian(mid);

	auto c_0 = a_L * b_L;

	auto c_2 = a_R * b_R;

	auto c_1 = (a_L + a_R) * (b_L + b_R) - c_0 - c_2;

	return c_0 + c_1.przesun_wielomian(mid) + c_2.przesun_wielomian(2 * mid);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int ilosc_1, ilosc_2;
	cin >> ilosc_1 >> ilosc_2;

	Wielomian wielomian_1;
	Wielomian wielomian_2;

	wielomian_1.resize(ilosc_1 + 1);
	wielomian_2.resize(ilosc_2 + 1);

	for(int i = 1; i <= ilosc_1; i++)
	{
		cin >> wielomian_1[i];
	}

	for(int i = 1; i <= ilosc_2; i++)
	{
		cin >> wielomian_2[i];
	}

	cout << "  *\n";
	cout << " ***\n";
	cout << "  *\n";
	cout << " ***\n";
	cout << "*****\n";

	auto wynik = wielomian_1 * wielomian_2;

	for(int i = 1; i < ilosc_1 + ilosc_2 + 1; i++)
	{
		cout << wynik[i] << " ";
	}

	cout << "\n";
	return 0;
}