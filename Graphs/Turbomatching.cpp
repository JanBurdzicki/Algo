// Raczej OK, ale niesprawdzone
#include<bits/stdc++.h>
using namespace std;

constexpr int M=1e5+7;

vector<int>g[M];
int matched[M];
bool o[M];

bool dfs(int v){
	if(o[v]) return false;
	o[v] = 1;

	for(auto w:g[v]){
		if(o[w] || !matched[w]) continue;
		matched[w] = v;
		matched[v] = w;
		return true;
	}

	for(auto w:g[v]){
		if(o[w] || !dfs(matched[w]) ) continue;
		matched[w] = v;
		matched[v] = w;
		return true;
	}

	return false;
}

int main(){
	int n, m, a, b;

	cin >> n >> m;
	for(int i=1; i<=m; i++){ //zakładamy, że graf jest dwudzielny
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	bool ok = 1;
	while(ok){
		ok = 0;
		for(int j=1; j<=n; j++) o[j] = 0;
		for(int j=1; j<=n; j++) if(!matched[j]) ok |= dfs(j);
	}
}