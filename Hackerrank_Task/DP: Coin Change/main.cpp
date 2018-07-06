// Problem : https://www.hackerrank.com/challenges/ctci-coin-change/problem

#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef vector<lli> vi;
typedef vector<vi> vvi;

vvi table;
vi denoms;

lli ways(lli amount, lli idx)
{
    if (table[amount][idx] != -1) return table[amount][idx];

    lli count = 0;
    for (lli i = idx; i < denoms.size(); ++i)
    {
        lli rest = amount - denoms[i];
        if (rest < 0) continue;
        if (table[rest][i] == -1) table[rest][i] = ways(rest, i);
        count += table[rest][i];
    }
    return count;
}

int main()
{
    lli n, m; cin >> n >> m;
    for (lli i = 0; i < m; ++i)
    {
        lli v; cin >> v;
        if (v <= n) denoms.push_back(v);
    }
    m = denoms.size();

    if (m == 0)
    {
        printf("%d", 0);
        return 1;
    }

    sort(begin(denoms), end(denoms), [](lli i, lli j){ return j < i; });
    table.resize(n + 1, vi(m, -1));
    for (lli i = 0; i < m; ++i) table[0][i] = 1;
    lli count = ways(n, 0);
    printf("%llu", count);

    return 0;
}
