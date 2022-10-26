#include <bits/stdc++.h>
using namespace std;

struct Punkt
{
	int x, y;

	bool operator < (const Punkt& inny) const
	{
		return x < inny.x || (x == inny.x && y < inny.y);
	}
};

bool clockwise(Punkt& a, Punkt& b, Punkt& c)
{
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool counterclockwise(Punkt& a, Punkt& b, Punkt& c)
{
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

void znajdz_convex_hull(vector <Punkt>& punkty, vector <Punkt>& convex_hull)
{
	if((int) punkty.size() == 1)
	{
		return;
	}

	sort(punkty.begin(), punkty.end());

	Punkt punkt_1 = punkty[0], punkt_2 = punkty.back();

	vector<Punkt> up, down;

	up.push_back(punkt_1);
	down.push_back(punkt_1);

	for(int i = 1; i < (int) punkty.size(); i++)
	{
		if(i == (int) punkty.size() - 1 || clockwise(punkt_1, punkty[i], punkt_2))
		{
			while((int) up.size() >= 2 && !clockwise(up[(int) up.size() - 2], up[(int) up.size() - 1], punkty[i]))
			{
				up.pop_back();
			}

			up.push_back(punkty[i]);
		}

		if(i == (int) punkty.size() - 1 || counterclockwise(punkt_1, punkty[i], punkt_2))
		{
			while((int) down.size() >= 2 && !counterclockwise(down[(int) down.size() - 2], down[(int) down.size() - 1], punkty[i]))
			{
				down.pop_back();
			}

			down.push_back(punkty[i]);
		}
	}

	for(int i = 0; i < (int) up.size(); i++)
	{
		convex_hull.push_back(up[i]);
	}

	for(int i = (int) down.size() - 2; i > 0; i--)
	{
		convex_hull.push_back(down[i]);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector <Punkt> punkty(n);

	for(int i = 0; i < n; i++)
	{
		cin >> punkty[i].x >> punkty[i].y;
	}

	vector <Punkt> convex_hull;

	znajdz_convex_hull(punkty, convex_hull);

	for(auto& x : convex_hull)
	{
		cerr << "D: " << x.x << " " << x.y << "\n";
	}

	return 0;
}
