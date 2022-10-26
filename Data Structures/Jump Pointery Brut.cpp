#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
#define lg(a) (31-__builtin_clz(a))
const int LIM=2e5+7, LG=10;//20;
vector<int>V;
int T[LIM], nxt[LIM][LG], kiedy[LIM];
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	rep(i, n) {
		cin >> T[i];
		if(T[i]==1) V.pb(i);
	}
	for(int i=n-1; i>=0; --i) {
		if(kiedy[T[i]+1]) {
			nxt[i][0]=kiedy[T[i]+1];
		} else nxt[i][0]=n;
		kiedy[T[i]]=i;
	}
	rep(i, LG) nxt[n][i]=n;
	for(int i=1; i<LG; ++i) {
		rep(j, n)
		{
			nxt[j][i]=nxt[nxt[j][i-1]][i-1];

			cerr << "D: " << nxt[j][i] << " ";
		}

		cerr << "\n";
	}

	return 0;

	while(m--) {
		int l, r;
		cin >> l >> r; --l; --r;
		auto it=lower_bound(all(V), l);
		int ans=1, akt=it-V.begin();
		if(akt==V.size()) {
			cout << "0\n";
			continue;
		}
		akt=V[akt];
		for(int i=LG-1; i>=0; --i) if(nxt[akt][i]<=r) {
			akt=nxt[akt][i];
			ans+=(1<<i);
		}
		cout << ans << '\n';
	}
}

