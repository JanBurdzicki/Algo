#include<bits/stdc++.h>
using namespace std;
#define rep(a, b) for(int a = 0; a < (b); ++a)
const int LIM=2e5+7, LG=20;
int T[LIM], nxt[LIM][LG], kiedy[LIM], jeden[LIM];
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	rep(i, n) cin >> T[i];
	kiedy[1]=n;
	for(int i=n-1; i>=0; --i) {
		nxt[i][0]=n;
		if(kiedy[T[i]+1]) nxt[i][0]=kiedy[T[i]+1];
		kiedy[T[i]]=i;
		jeden[i]=kiedy[1];
	}
	rep(i, LG) nxt[n][i]=n;
	for(int i=1; i<LG; ++i) {
		rep(j, n) nxt[j][i]=nxt[nxt[j][i-1]][i-1];
	}
	while(m--) {
		int a, b, ans=1;
		cin >> a >> b; --a; --b;
		a=jeden[a];
		if(a>b) {
				cout << "0\n";
				continue;
		}
		for(int i=LG-1; i>=0; --i) if(nxt[a][i]<=b) {
				ans+=1<<i;
				a=nxt[a][i];
		}
		cout << ans << '\n';
	}
}