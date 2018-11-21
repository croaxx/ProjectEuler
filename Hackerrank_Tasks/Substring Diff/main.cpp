// Problem definition : https://www.hackerrank.com/challenges/substring-diff/problem
// Time complexity: O(n^2); space complexity O(1)
#include <iostream>
#include <algorithm>

using namespace std;

int compute_window(const string &s1, const string &s2, int start1, int start2, int diff_max)
{
    const int N = (int)s1.size();
    int max_length = -1, diffs = 0;
    int end1 = start1, end2 = start2;

    while (end1 != N && end2 != N)
    {
        while (end1 < N && end2 < N)
        {
            if (s1[end1] != s2[end2]) ++diffs;
            end1++; end2++;
            if (diffs > diff_max) break;
            max_length = std::max(max_length, end1 - start1);
        }

        while (diffs > diff_max && start1 < N && start2 < N)
        {
            if (s1[start1] != s2[start2]) --diffs;
            ++start1; ++start2;
        }
    }
    return max_length;
}

int longest_common_substring(const string& s1, const string& s2, int k)
{
    int lcs = -1;
    for (int i = 0; i < (int)s1.size(); ++i)
    {
        lcs = std::max(lcs, compute_window(s1, s2, 0, i, k));
        lcs = std::max(lcs, compute_window(s1, s2, i, 0, k));
    }
    return lcs;
}

int main()
{
    int tests; cin >> tests;
    for (int t = 0; t < tests; ++t)
    {
        int k; cin >> k;
        string s1, s2; cin >> s1 >> s2;
        int lcs = longest_common_substring(s1, s2, k);
        printf("%d\n", lcs);
    }
    return 0;
}