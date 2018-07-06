// Problem definition: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1245

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi table;
vi freq;
vi prefix_sum;

const int INF = (~0u) / 2;

int min_cost(int L, int R, int level)
{
    if (L > R) return 0;
    else if (table[L][R] != -1)
    {
        int ans = table[L][R] + (level - 1) * prefix_sum[R];
        if (L > 0) ans -= (level - 1) * prefix_sum[L-1];
        return ans;
    }

    int cost = INF;
    for (int i = L; i <= R; ++i)
    {
        int cost_node = freq[i] * level;
        int cost_L = min_cost(L, i - 1, level + 1);
        int cost_R = min_cost(i + 1, R, level + 1);
        cost = std::min(cost, cost_node + cost_L + cost_R);
    }

    table[L][R] = cost - (level - 1) * prefix_sum[R];
    if (L > 0) table[L][R] += (level - 1) * prefix_sum[L-1];

    return cost;
}

auto main() -> int
{
    int n;
    while (cin >> n)
    {
        freq.resize(n, 0);
        table.assign(n, vi (n, -1));
        for (int i = 0; i < n; ++i) cin >> freq[i];
        prefix_sum = freq;
        for (int i = 1; i < n; ++i) prefix_sum[i] += prefix_sum[i-1];
        int cost = min_cost(0, n - 1, 0);
        printf("%d\n", cost);
    }
}
