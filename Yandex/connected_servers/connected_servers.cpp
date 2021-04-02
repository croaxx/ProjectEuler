/*
Problem description: https://contest.yandex.ru/contest/19036/problems/E
Solution complexity:
    time: O(QK(alpha(N))~O(QK), alpha(N) - iterated logarithm (nearly constant).
    space: - O(N) (hash map, array of connection pairs, UnionFind structure).

Solution:
    The task boils down to answering the queries of the type "Does the server
    with an ID_i belong to the same cluster (or union) as the server with ID_j".
    Answering these queries efficiently (in nearly in O(1)) can be done with the
    data structure called UnionFind (or Disjoint-set). To build this structure
    from the connections between servers, we first need to know the total number
    of servers M and then perform merging of the servers into clusters using an
    operation `union_set(i, j)`, where 0<=i<M and 0<=j<M are the indices of the
    two connected servers (these indices are different from the IDs). Therefore,
    we need to find the total number of servers M and also map servers' IDs to
    the indices ranging from 0 to M-1. Both goals can be achieved with an
    additional hash map. This hash map can be build during the read of the input
    data. The keys of this hash map are intergers, holding IDs and values are
    integers, holding the index (current map size). Size of the resulting hash
    map is the number of servers M. After that we can build the clusters by
    iterating over connection pairs and using our hash map for translating IDs
    into indices. Once the UnionFind structure is built answering the queries is
    easy thanks to `is_same_set(i, j)` function, which tells if servers with
    indices i and j belong to the same cluster.
*/

#include <stdio.h>

#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

using VectorInt = vector<int>;
using PairInts = pair<int, int>;
using MapInts = unordered_map<int, int>;

class UnionFind
{
    /*
    This data structure is taken from the book
    `Competitive Programming 3` by S.Halim and F.Halim.
    */
private:
    VectorInt p, rank;
    int count;

public:
    UnionFind(int N)
    {
        count = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }

    int find_set(int i) { return (p[i] == i) ? i : (p[i] = find_set(p[i])); }

    bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

    void union_set(int i, int j)
    {
        if (!is_same_set(i, j))
        {
            int x = find_set(i), y = find_set(j);
            if (rank[x] > rank[y])
                p[y] = x;
            else
            {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
            --count;
        }
    }
};

VectorInt find_connected_servers(int X, UnionFind &uf, const MapInts &map_ii,
                                 const VectorInt &IDs)
{
    VectorInt servers;
    int from_server = map_ii.find(X)->second;
    for (auto id : IDs)
    {
        int to_server = map_ii.find(id)->second;
        if (uf.is_same_set(to_server, from_server))
            servers.emplace_back(id);
    }
    return servers;
}

int main()
{
    int N, Q;
    scanf("%d", &N);
    MapInts map_ii;
    vector<PairInts> connections(N);
    for (int i = 0; i < N; ++i)
    {
        int A, B;
        scanf("%d %d", &A, &B);
        auto it = map_ii.find(A);
        if (it == end(map_ii))
            map_ii.emplace(A, (int)map_ii.size());
        it = map_ii.find(B);
        if (it == end(map_ii))
            map_ii.emplace(B, (int)map_ii.size());
        connections[i] = PairInts(A, B);
    }
    // Group servers into clusters using ingenious UnionFind (Disjoint-set).
    UnionFind union_find(map_ii.size());
    for (auto p : connections)
    {
        if (!union_find.is_same_set(map_ii[p.first], map_ii[p.second]))
            union_find.union_set(map_ii[p.first], map_ii[p.second]);
    }
    // Respond to Q queries
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i)
    {
        int X, K;
        scanf("%d %d", &X, &K);
        VectorInt IDs(K);
        for (int j = 0; j < K; ++j)
            scanf("%d", &IDs[j]);
        auto servers = find_connected_servers(X, union_find, map_ii, IDs);
        printf("%zd ", servers.size());
        for (auto id : servers)
            printf("%d ", id);
        printf("\n");
    }
    return 0;
}
