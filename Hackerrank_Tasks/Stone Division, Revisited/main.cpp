// Problem definition : https://www.hackerrank.com/challenges/stone-division-2/problem

#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vi;
typedef unordered_map<ull, ull> mapii; // memoization table: (stones in a pile - max moves for this pile)

ull divide(ull n, const vi& s, mapii& m)
{
    auto it = m.find(n);
    if (it != end(m)) { return it->second; }
    ull moves = 0;
    for (int i = 0; i < (int)s.size(); ++i)
    {
        if (n != s[i])
        {
            ull div = n / s[i];
            if (div * s[i] == n)
                moves = std::max(moves, 1 + div * divide(s[i], s, m));
        }
    }
    m[n] = moves;
    return moves;
}

int main()
{
    int q; cin >> q;
    for (int qi = 0; qi < q; ++qi)
    {
        ull n; int m; cin >> n >> m;
        vi s;
        for (int i = 0; i < m; ++i)
        {
            ull si; cin >> si;
            s.push_back(si);
        }
        mapii mp;
        ull moves = divide(n, s, mp);
        printf("%llu\n", moves);
    }
    return 0;
}
