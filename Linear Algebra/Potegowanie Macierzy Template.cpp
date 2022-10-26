/**
 * Autor: Andrzej Radzimiński
 * Jeśli coś jest nie jasne, lub chcecie zgłosić uwagi/błędy, piszcie przez sio lub osobiście.
 *
 *
 * Co jest gdzie (w liniach):
 * struct: 24
 * pola struct-a: 29
 * metody struct-a: 93
 * używanie klas (struct-ów): 153
 * operator*: 55
 * operator* poza klasa: 108
 * const, znaczek `&`: 65
 * operator= : 174
 * potęgowanie macierzy: 131
 * przykład z ciągiem Fibonacciego: 185
 */

#include <iostream>
#include <cassert> //assert
using namespace std;

/**
 * struct, czyli „Nowy typ danych”.
 * Przypomnienie: klasa == struct, różni się tylko o private/public
 */
struct Matrix22 {
	/**
	 * Pola klasy, czyli dane zawarte w typie Matrix22.
	 * Ustawione w kwadracie jak w macierzy.
	 */
	int a, b;
	int c, d;

	/**
	 * Metoda ustawiająca wszystkie zmienne na dane wartości.
	 * Uwaga: To powinien być „konstuktor”, ale tego nie pokazaliśmy.
	 */
	void ustawNa(int x, int y, int z, int w) {
		a = x;
		b = y;
		c = z;
		d = w;
		/**
		 * Hint: nazwa parametru może być taka sama jak pole klasy, np:
		 *  `void ustawNa(int a, int b, int c, int d)`
		 *
		 * Wtedy aby używać pola klasy, a nie argumentu funkcji piszemy: `this->a`.
		 * Czyli np: `this->a = a;`
		 * Wtedy `this->a` to pole klasy, a `a` to argument.
		 */
	}

	/**
	 * Możemy przeciążyć operator mnożenia,
	 * czyli napisać funkcję, którą wykonujemy przez użycie opertora.
	 *
	 * Taki operator przyjmuje zawsze dwie wartości, ale jeśli piszemy go w klasie
	 * pierwsza wartość jest „domyśla” i jest nią zmienna (obiekt), na którym używamy metody.
	 *
	 * Inaczej mówiąc możemy używać tutaj: a, b, c, d i jest to jeden argument mnożenia.
	 * Czyli w `m * k`: `k` to `other`, `m` to nasze `a, b, c, d` z linii 32.
	 *
	 * Uwaga:
	 * znaczek `&` oznacza, że przekazujemy nie kopię,
	 * ale referencję na argument. Czyli jeśli coś tu zmienimy to
	 * zmieni się również w zmiennej którą tu przekazaliśmy
	 * (a konkretnej to praktycznie ta sama zmienna).
	 *
	 * słowo `const` oznacza, że nie możemy wykonywać, żadnych
	 * modyfikacji na other.
	 * Gdy callujemy metody na zmiennej const, metody też muszą być const - o tym nie mówiliśmy
	 */
	Matrix22 operator*(const Matrix22& other) {
		Matrix22 wynik;
		/**
		 * mnożenie macierzy (wynik = ja * other)
		 * tak jak wzorki w:
		 *                          | e f |  <-- other
		 *                          | g h |  <--
		 *
		 * nasza klasa --> | a b |  | ? ? |  <-- wynik
		 *             --> | c d |  | ? ? |  <--
		 */
		wynik.a = a * other.a + b * other.c;
		wynik.b = a * other.b + b * other.d;
		wynik.c = c * other.a + d * other.c;
		wynik.d = c * other.b + d * other.d;
		return wynik;
	}

	/**
	 * Możemy też napisać po po prostu taką metodę.
	 * Metod się używa, tak jak push_back w vector-rze (przykład w main-nie).
	 * Możemy tu korzystać z `a`, `b`, `c`, `d`, i gdy je modyfikujemy, to
	 * modyfikują się pola w zmiennej z której call-ujemny metodę.
	 * Implementację pominąłem jako, że jest taka sama jak w `operator*`.
	 */
	Matrix22 multiply(const Matrix22& other) {
		Matrix22 wynik;
		//mnożenie macierzy (wynik = ja * other)
		return wynik;
	}

};

/**
 * Operator mnożenia macierzy możemy napisać również tak (implementacja w klasie jest wyżej).
 * Póki to jest operator piszcie jak wolicie, tak może być prościej zrozumieć.
 * Ale na przyszłość pisany w klasie,
 * raczej lepiej pokazuje nam co się dzieje w kodzie.
 *
 * Implementację pominąłem jako, że jest taka sama jak wyżej.
 *
 * Uwaga: Gdy zaimplementujemy operator (o tej samej deklaracji,
 * czyli zwracające i przyjmujące te same typu zmiennych)
 * na dwa sposoby w jednym kodzie kompilator na nas
 * nakrzyczy bo nie będzie wiedział której implementacji użyć.
 *
 * W tym kodzie nie krzyczy, bo 74, nie ma magicznego `const` o którym nie mówiliśmy,
 * ale wpisanie dwóch takich funkcji i tak nie jest dobrym pomysłem i może generować bugi.
 */
Matrix22 operator*(const Matrix22& a, const Matrix22& b) {
	Matrix22 wynik;
	//mnożenie macierzy (wynik = ja * other)
	return wynik;
}


/**
 * Funkcja potęgująca macierze.
 * Dokłądnie tak samo jak szybkie potegowanie int-ów.
 */
Matrix22 matrix_power(const Matrix22& base, int exponent) {
	if (exponent == 0) {
		//Zwracamy element neutralny mnożenia:
		Matrix22 out;
		out.ustawNa(1, 0, 0, 1);
		return out;
	}

	Matrix22 half = matrix_power(base, exponent / 2);

	if (exponent % 2 == 0) {
		return half * half;
	}

	return half * half * base;
}

int main() {
	/**
	 * Tak definiujemy zmienne typu Matrix22.
	 * Czyli tak samo jak int, double, vector<int>, ...
	 */
	Matrix22 a;
	Matrix22 b;
	Matrix22 c;

	/**
	 * Dostęp do elementów Matrix22:
	 * [nazwa zmiennej].[nazwa pola lub metody],
	 * czyli:
	 */
	a.a = 2;
	a.ustawNa(0, 0, 0, 1);
	b.ustawNa(1, 1, 1, 1);
	cout << "Wartości a.b, b.c: " << a.b << " " << b.c << "\n";

	/**
	 * Użycie operatora `*` w macierzach (tak jak metody)
	 * Wynik przypisujemy do `c`:
	 *
	 * Uwaga: operator `=` jest tworzony przez kompilator
	 * automatycznie, i jest to przypisanie każdego pola klasy z jednej do drugiej.
	 * Teraz jest to wygodne, ale trzeba na to uważać, bo może to
	 * robić coś innego niż się spodziewaliśmy (lub się w ogóle nie stworzyć),
	 * gdy np używamy tablic lub typów z stl-a.
	 * Operator `=` możemy napisać sami, pisząc go tak samo jak operator `*`.
	 */
	c = a * b;


	/**
	 * Przykłąd z ciągiem Fibonacciego:
	 */

	int k;
	cout << "Podaj którą liczbę Fibonacciego chcemy obliczyć: ";
	cin >> k;
	assert(k >= 1); //dla k < 1 program się zakończy błędem

	//macierz wyznaczania kolejnych elementow ciągu:
	Matrix22 matrix_next;
	matrix_next.ustawNa(0, 1, 1, 1);

	/**
	 * Macierz wyznaczająca k-ty element ciągu:
	 *
	 * (`k - 1` ponieważ do uzyskania k-tej liczby musimy "przesunąć" pierwszą o k - 1).
	 */
	Matrix22 fibb_k = matrix_power(matrix_next, k - 1);

	/**
	 * `1 * fibb_k.b + 0 * fibb_k.d ` symbolizuje mnożenie [0 1] przez naszą macierz
	 */
	cout << "K-ta liczba Fibonacciego to: " << 0 * fibb_k.b + 1 * fibb_k.d << "\n";
	return 0;
}