struct HopcroftKarp
{
    int n, m;
    vector <vector <pair <int, int> > > graph;
    vector <pair <int, int> > previous;
    vector <int> freeV;
    vector <int> matchE;
    vector <int> vis;
    vector <int> layers;
    vector <int> V;

    HopcroftKarp(int n, int m) : n(n), m(m)
    {
        graph.resize(n + m);
        previous.resize(n + m);
        freeV.resize(n + m, 1);
        vis.resize(n + m);
        layers.resize(n + m);
    }

    void addEdge(int a, int b)
    {
        b += n;
        graph[a].PB(MP(b, SIZE(matchE)));
        graph[b].PB(MP(a, SIZE(matchE)));
        matchE.PB(0);
    }

    void BFS()
    {
        int finalLayer = INF;
        queue <int> bfs;
        FOR(i, 0, n + m)
        {
            layers[i] = -1;
            if(freeV[i] && i < n)
            {
                bfs.push(i);
                layers[i] = 0;
            }
        }
        while(SIZE(bfs))
        {
            int v = bfs.front();
            bfs.pop();
            if(freeV[v] && v >= n)
            {
                V.PB(v);
                finalLayer = layers[v];
            }
            if(layers[v] >= finalLayer)
                continue;
            for(auto& u : graph[v])
            {
                if(layers[u.first] == -1 && ((v < n && !matchE[u.second]) || (v >= n && matchE[u.second])))
                {
                    layers[u.first] = layers[v] + 1;
                    bfs.push(u.first);
                }
            }
        }
    }

    int DFS(int v, int match = false)
    {
        vis[v] = 1;
        if(!layers[v])
            return v;
        for(auto& u : graph[v])
        {
            if(!vis[u.first] && layers[u.first] == layers[v] - 1 && match == matchE[u.second])
            {
                previous[u.first] = MP(v, u.second);
                int t = DFS(u.first, match ^ 1);
                if(t != -1)
                    return t;
            }
        }
        return -1;
    }

    int MaxMatching()
    {
        int res = 0;
        while(true)
        {
            V.clear();
            BFS();
            if(!SIZE(V))
                break;
            for(auto& v : vis)
                v = 0;
            for(auto& v : V)
            {
                int x = DFS(v);
                if(x != -1)
                {
                    ++res;
                    while(x != v)
                    {
                        matchE[previous[x].second] ^= 1;
                        freeV[x] = 0;
                        x = previous[x].first;
                    }
                    freeV[v] = 0;
                }
            }
        }

        return res;
    }
};