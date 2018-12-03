// Problem description : https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages/0
// Complexity: O(M*N^2)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int INF = int(~0u / 2);

int min_pages(const vi& A, vvi& memo, const vi& prefix_sum, int books, int students)
{
    if (books < students) return -1;

    int from = (int)A.size() - books;
    int prefix = from == 0 ? 0 : prefix_sum[from-1];

    if (students == 1) return prefix_sum.back() - prefix;
    else if (memo[books][students] != -1) return memo[books][students];

    int pages_min = INF;
    for (int to = from; to < (int)A.size(); ++to)
    {
        int p1 = prefix_sum[to] - prefix;
        int p2 = min_pages(A, memo, prefix_sum, books - to + from - 1, students - 1);
        if (p2 != -1) pages_min = min(pages_min, max(p1, p2));
    }

    memo[books][students] = pages_min;
    return pages_min;
}

int main()
{
    int tests; cin >> tests;
    vi results;
    for (int t = 0; t < tests; ++t)
    {
        int N; cin >> N;
        vi A(N), prefix_sum(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> A[i];
            if (i == 0) prefix_sum[i] = A[i];
            else prefix_sum[i] = A[i] + prefix_sum[i-1];
        }
        int M; cin >> M;
        vvi memo(N + 1, vi(M + 1, -1));
        int min_pages = min_pages(A, memo, prefix_sum, N, M);
        results.push_back(min_pages);
    }
    for (const auto& e : results) printf("%d\n", e);
    return 1;
}
