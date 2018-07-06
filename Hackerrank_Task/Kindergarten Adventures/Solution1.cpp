// Problem definition : https://www.hackerrank.com/challenges/kindergarten-adventures/problem

#include <iostream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
#define ASSERT assert

// this class is a modification of the "Segment Tree"
class SumTree
{
public:
    vi _st;
    int _n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    SumTree(int n)
    {
        _n = n;
        _st.assign(4 * _n, 0);
    }

    void update_range(int i, int j, int v)
    {
        update_range(1, 0, _n - 1, i, j, v);
    }

    void update_range(int p, int L, int R, int i, int j, int v)
    {
        if (i > R || j < L) return;
        if (L >= i && R <= j)
        {
            _st[p] += v;
            return;
        }
        update_range(left(p) , L, (L+R) / 2, i, j, v);
        update_range(right(p), (L+R) / 2 + 1, R, i, j, v);
    }

    void sum_paths()
    {
        for (int i = 1; i <= _n; ++i)
        {
            _st[left(i)] += _st[i];
            _st[right(i)] += _st[i];
        }
    }
};

int main()
{
    int n; cin >> n;
    int k = 1; while (k < n) { k <<= 1; }
    SumTree tree(k);
    for (int i = 0; i < n; ++i)
    {
        int a; cin >> a;
        // student with an index i will finish on time,
        // if the teacher starts at the following index-ranges [L, R]
        // we update the SumTree nodes for these ranges
        int L, R;
        if (a == 0)
        {
            L = 0; R = n - 1;
            tree.update_range(L, R, 1);
        }
        else
        {
            if (a <= i)
            {
                L = 0; R = i - a;
                tree.update_range(L, R, 1);
            }
            if (a < n)
            {
                L = i + 1;
                R = min(n - a + i, n - 1);
                if (R >= L) { tree.update_range(L, R, 1); }
            }
        }
    }

    tree.sum_paths(); // calculate sums at the nodes [0,0], [1, 1], ... , [n-1, n-1]

    int max_val = -1, idx = -1;
    for (int i = 0; i < n; ++i)
    {
        int node_value = tree._st[k+i];
        if (max_val < node_value)
        {
            max_val = node_value;
            idx = i + 1;
        }
    }
    printf("%d\n", idx);
    return 0;
}
