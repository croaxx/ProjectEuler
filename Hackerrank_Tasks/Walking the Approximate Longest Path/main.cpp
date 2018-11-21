// Problem definition : https://www.hackerrank.com/challenges/walking-the-approximate-longest-path/problem

#include <iostream>
#include <stdio.h>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef unordered_set<int> seti;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef queue<int> qi;

const int INF = 10000000;

struct Vertex
{
    seti neigh;
};

pair<int, int> get_min_neighbour(vector<Vertex>& g, int v, vb& visited)
{
    int v1 = INF, v2 = INF, idx1 = INF, idx2 = INF;
    for (const auto& e : g[v].neigh)
    {
        if (!visited[e])
        {
            int count = 0;
            for (const auto& ee : g[e].neigh)
                if (!visited[ee]) ++count;

            if (v1 > count)
            {
                v1 = count;
                idx1 = e;
            }

            if (v2 > count && count >= 2)
            {
                v2 = count;
                idx2 = e;
            }
        }
    }
    return make_pair(idx1, idx2);
}

vi find_max_distance(vector<Vertex>& g)
{
    int min_v = INF;
    int min_idx = 0;
    int idx = 0;
    for (const auto& e : g)
    {
        int size = (int)e.neigh.size();
        if (min_v > size)
        {
            min_v = size;
            min_idx = idx;
        }
        ++idx;
    }

    vb visited(g.size(), false); visited[min_idx] = true;
    vi vertices{min_idx};
    while (true)
    {
        auto neighbs = get_min_neighbour(g, min_idx, visited);
        if (neighbs.first == INF && neighbs.second == INF)
            break;
        else if (neighbs.second != INF)
        {
            visited[neighbs.second] = true;
            vertices.push_back(neighbs.second);
            min_idx = neighbs.second;
        }
        else
        {
            visited[neighbs.first] = true;
            vertices.push_back(neighbs.first);
            min_idx = neighbs.first;
        }
    }
    return vertices;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Vertex> g(n);
    for (int i = 0; i < m; ++i)
    {
        int x, y; cin >> x >> y;
        g[x-1].neigh.insert(y-1);
        g[y-1].neigh.insert(x-1);
    }
    vi vertices = find_max_distance(g);
    printf("%zd\n", vertices.size());
    for (const auto& e : vertices) printf("%d ", e + 1);
    return 0;
}
