// Problem description: https://practice.geeksforgeeks.org/problems/travelling-salesman-problem/0
// Solution time complexity: O(N^2*2^N)

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int INF = INT32_MAX;

int min_cost(int pos, int visited, const vvi& M, vvi& memo)
{
    // go back to the start, if all cities are visited
    if (visited == INF) return M[pos][0];

    // extract N last bits to get the state of visited cities
    int state = ((1 << M.size()) - 1) & visited;

    // check if state was already computed, then just return it
    if (memo[pos][state] != -1) return memo[pos][state];

    int cost_min = INF;
    for (int i = 0; i < (int)M.size(); ++i)
    {
        // check if i-th city is visited by looking at its bit
        if (!(visited & (1 << i)))
        {
            visited |= 1 << i; // set i-th bit on
            int cost = M[pos][i] + min_cost(i, visited, M, memo);
            cost_min = min(cost_min, cost);
            visited ^= 1 << i; // backtrack, flip i-th bit
        }
    }

    memo[pos][state] = cost_min;
    return cost_min;
}

int main()
{
    int tests; cin >> tests;
    vi results;
    for (int test = 0; test < tests; ++test)
    {
        int N; cin >> N; // read the number of cities

        vvi M(N, vi(N, -1)); // read the adjacency matrix
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> M[i][j];

        int states = 1 << N; // 2^N different states of visited cities
        vvi memo(N, vi(states, -1)); // memoization of N*2^N states, memo[last visited city][visited cities state]
        int visited = INF ^ (states - 1);// define the mask, e.g., 1111100000 (last N bits are zeros)
        visited |= 1; // set the first city as visited: 1111100001
        int cost = min_cost(0, visited, M, memo);
        results.push_back(cost);
    }
    for (const auto& e : results) printf("%d\n", e);
    return 0;
}