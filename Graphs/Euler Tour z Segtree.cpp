
vector <Krawedz> graf[MAX_N];

vector <int> preorder(MAX_N);
vector <int> postorder(MAX_N);

vector <Krawedz> euler_tour(2 * MAX_N);

int timer;

void DFS(int v, int poprzednik, int poprzednia_waga)
{
	timer++;

	preorder[v] = timer;

	euler_tour[timer] = {v, poprzednia_waga};

	for(auto& krawedz : graf[v])
	{
		int sasiad = krawedz.sasiad;
		int waga = krawedz.waga;

		if(sasiad != poprzednik)
		{
			DFS(sasiad, v, waga);
		}
	}

	timer++;

	postorder[v] = timer;

	euler_tour[timer] = {v, poprzednia_waga};
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, t;
	cin >> n >> t;

	for(int i = 0; i < n - 1; i++)
	{
		int a, b, waga;
		cin >> a >> b >> waga;

		graf[a].push_back({b, waga});
		graf[b].push_back({a, waga});
	}

	// Zeby moc zastosowac Mo na drzewie, to musimy przestawic drzewo jako jakas tablice
	// Zrobimy to za pomoca Euler Toura, czyli wchodzac do wierzcholka i z niego wychodzac,
	// Wrzucamy go do tablicy z waga do ojca, czyli {v, poprzednia_waga}
	// Zapisujemy sobie rowniez preordery (pierwsze wystapienie wierzcholka w naszej tablicy)

	DFS(1, 0, INF);

	vector <Zapytanie> zapytania(t);

	for(int i = 0; i < t; i++)
	{
		int a, b;
		cin >> a >> b;

		if(preorder[a] > preorder[b])
		{
			swap(a, b);
		}

		// Poniewaz LCA(a, b) nie nalezy do interesujacego nas przedzialu
		// Oby dwa wystapienia beda poza przedzialem [preorder[a], preorder[b]]
		// Chyba, ze a == LCA, wtedy preorder[a] odpowiada za LCA
		// Dlatego mozemy uzyc syna wierzcholka a, czyli preorder[a] + 1

		zapytania[i].L = preorder[a] + 1;
		zapytania[i].R = preorder[b];

		zapytania[i].indeks = i;
	}