#include <bits/stdc++.h>
using namespace std;

// Algorytm jest bardzo podobny do Edmond - Karp do liczenia Max Flow
// Analogicznie jak w Edmond - Karp: O(n * m) * czas_znalezienia_najkrotszych_sciezek
// Dijkstra -> O(n ^ 3 * m) -> mamy doczynienia z ujemnymi wagami, wiec trzeba by ja pozmieniac, bo czysta nie dziala
// Bellman - Ford -> O(n ^ 2 * m ^ 2)
// SPFA do najkrotszych sciezek

// Jesli mamy graf nieskierowany, to dajemy 2 krawedzie skierowane w przeciwna strone
// Kazda krawedz ma back edge
// Dlatego dla kazdej krawedzi nieskierowanej finalnie mamy 4 krawedzie
// Trzymamy sobie flow osobno dla kazdej skierowanej krawedzi
// Przy szukaniu najkrotszych sciezek wazne jest ktora krawedzia przechodzimy, wiec trzymamy sobie numer krawedzi,
// Ktora przeszlismy i wierzcholek z ktorego wychodzimy
// Zmniejszajac flow w back edge musimy wiedziec jakiej krawedzi ta krawedz odpowiada
// Wiec trzymamy sobie dla kazdej krawedzi numer krawedzi back edge

struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}


int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	return 0;
}



/*
class MinCostMaxFlow
{
public:
    struct Edge
    {
        int source, dest, rev;
        LL flow, cost;
        Edge(int source, int dest, LL flow, int rev, LL cost) : source(source), dest(dest), flow(flow), rev(rev), cost(cost) {}
    };

    int N;
    vector <Edge> edges;
    vector <LL> dist;
    vector <int> prevv;
    vector <vector <int> > graph;

    MinCostMaxFlow(int n)
    {
        N = n;
        graph.resize(n);
        dist.resize(n);
        prevv.resize(n);
    }

    void addEdge(int a, int b, LL cost, LL cap)
    {
        int ID = SIZE(edges);
        edges.PB(Edge(a, b, cap, ID + 1, cost));
        edges.PB(Edge(b, a, 0, ID, -cost));
        graph[a].PB(ID);
        graph[b].PB(ID + 1);
    }

    void SPFA(int start)
    {
        FOR(i, 0, N) dist[i] = LLINF;
        vector <bool> inqueue(N, 0);

        dist[start] = 0;
        queue <int> q;

        q.push(start);
        inqueue[start] = 1;

        while (SIZE(q))
        {
            int v = q.front();
            q.pop();
            inqueue[v] = 0;

            for (auto u : graph[v])
            {
                auto e = edges[u];
                if(!e.flow) continue;
                if (dist[v] + e.cost < dist[e.dest])
                {
                    dist[e.dest] = dist[v] + e.cost;
                    if (!inqueue[e.dest])
                    {
                        q.push(e.dest);
                        inqueue[e.dest] = 1;
                    }
                }
            }
        }
    }

    void Dijkstra(int start)
    {
        FOR(i, 0, N) dist[i] = LLINF;
        dist[start] = 0;
        set <pair <LL, LL> > dijkstra;
        dijkstra.insert(MP(0, start));

        while(SIZE(dijkstra))
        {
            auto v = dijkstra.begin()->second;
            dijkstra.erase(dijkstra.begin());

            for(auto& u : graph[v])
            {
                auto e = edges[u];
                if(!e.flow) continue;
                if(dist[v] + e.cost < dist[e.dest])
                {
                    dijkstra.erase(MP(dist[e.dest], e.dest));
                    dist[e.dest] = dist[v] + e.cost;
                    prevv[e.dest] = u;
                    dijkstra.insert(MP(dist[e.dest], e.dest));
                }
            }
        }
    }

    void ReduceCosts()
    {
        for(auto& e : edges)
            e.cost = e.cost + dist[e.source] - dist[e.dest];
    }

    LL calc(int start, int end)
    {
        SPFA(start);
        ReduceCosts();
        LL res = 0;
        LL temp = 0;

        while(true)
        {
            temp += dist[end];
            Dijkstra(start);
            if(dist[end] == LLINF) break;
            LL flow = LLINF;
            int v = end;
            while(v != start)
            {
                auto e = edges[prevv[v]];
                flow = min(flow, e.flow);
                v = e.source;
            }
            v = end;
            while(v != start)
            {
                auto& e = edges[prevv[v]];
                if(e.flow != LLINF) e.flow -= flow;
                if(edges[e.rev].flow != LLINF) edges[e.rev].flow += flow;
                v = e.source;
            }
            res += flow * (temp + dist[end]);
            ReduceCosts();
        }

        return res;
    }
};
*/