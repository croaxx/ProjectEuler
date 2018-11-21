// Problem definition : https://www.hackerrank.com/contests/w38/challenges/a-time-saving-affair

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
typedef long long int lli;
typedef pair<lli, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;

const lli INF = numeric_limits<lli>::max() / 2;

lli dijkstra(const vvpii& g, int k)
{
    if (g.size() == 1) { return 0; }
    int start = 0;
    vector<lli> dist(g.size(), INF);
    dist[start] = 0;
    priority_queue<pii, vpii, greater<pii>> pq;
    pq.push(make_pair(0, start));
    while (!pq.empty())
    {
        pii front = pq.top(); pq.pop();
        lli d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (int j = 0; j < (int)g[u].size(); j++)
        {
            pii v = g[u][j];
            lli d_tmp = dist[u];
            if (k == 1 && (d_tmp & 1)) { ++d_tmp; }
            else if ((d_tmp / k) & 1) { d_tmp += k - (d_tmp % k); }
            if (d_tmp + v.first < dist[v.second])
            {
                dist[v.second] = d_tmp + v.first;
                pq.push(make_pair(dist[v.second], v.second));
            }
        }
    }
    return dist[g.size() - 1];
}

auto main() -> int
{
    int n, k, m; cin >> n >> k >> m;
    vvpii graph(n);
    for (int i = 0; i < m; ++i)
    {
        int a, b, w; cin >> a >> b >> w;
        if (a == b) { continue; }
        graph[a-1].push_back(make_pair(w, b - 1));
        graph[b-1].push_back(make_pair(w, a - 1));
    }
    lli time_min = dijkstra(graph, k);
    cout << time_min << endl;
}
