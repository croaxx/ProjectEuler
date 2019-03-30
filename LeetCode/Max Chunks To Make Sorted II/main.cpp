// Problem description: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/

// Time complexity: O(nlogn) - O(n) build SegmentTree;
// O(logn) search for min element in the array using SegmentTree
// => O(nlogn) to iterate over the array and perform min query for each element
// Space complexity: O(n) - build SegmentTree

#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

class SegmentTree
{
private:
    vi st_min;
    vi A;
    int n;

    int left(int p) { return p << 1; }

    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R)
    {
        if (L == R)	st_min[p] = L;
        else
        {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st_min[left(p)], p2 = st_min[right(p)];
            st_min[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }

    int rmq_min(int p, int L, int R, int i, int j)
    {
        if (i > R || j < L) return -1;
        if (L >= i && R <= j) return st_min[p];
        int p1 = rmq_min(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq_min(right(p), (L + R) / 2 + 1, R, i, j);
        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return (A[p1] <= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vi &_A)
    {
        A = _A;
        n = (int)A.size();
        st_min.assign(4 * n, 0);
        build(1, 0, n - 1);
    }
    int rmq_min(int i, int j) { return rmq_min(1, 0, n - 1, i, j); }
};

class Solution
{
public:
    int maxChunksToSorted(vi& arr)
    {
        SegmentTree seg_tree(arr);
        int chunks = 1, pos = 0, max_lhs = arr[0], N = arr.size() - 1;
        while (pos < N)
        {
            max_lhs = max(max_lhs, arr[pos]); // maximum element before pos
            // arr[seg_tree.rmq_min(pos + 1, N)] - min element after pos
            while (pos < N && max_lhs > arr[seg_tree.rmq_min(pos + 1, N)]) // condition of chunk partitioning
            {
                ++pos;
                max_lhs = max(max_lhs, arr[pos]);
            }
            ++chunks; ++pos;
        }
        return pos == N + 1 ? chunks - 1 : chunks;
    }
};
