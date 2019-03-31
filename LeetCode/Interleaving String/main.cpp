// Problem description: https://leetcode.com/problems/interleaving-string/submissions/ 
// Time complexity: O(nm) - n, m sizes of s1 and s2, respectively
// Space complexity: O(nm) - 2D memoization table

#include <vector>

using namespace std;

class Solution
{
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    bool isInterleave(const string& s1, const string& s2, const string& s3)
    {
        if (s1.size() + s2.size() != s3.size()) return false;
        vvi memo(s1.size() + 1, vi(s2.size() + 1, -1));
        return isInterleave(s1, s2, s3, memo, 0, 0);
    }

    bool isInterleave(const string& s1, const string& s2,
                      const string& s3, vvi& memo, int idx1, int idx2)
    {
        if (idx1 == s1.size() && idx2 == s2.size()) return true;
        int& ans = memo[idx1][idx2];
        if (ans != -1) return ans;
        int idx3 = idx1 + idx2;
        if (!s1.empty() && idx1 < s1.size() && s1[idx1] == s3[idx3])
            if (isInterleave(s1, s2, s3, memo, idx1 + 1, idx2))
                return ans = true;
        if (!s2.empty() && idx2 < s2.size() && s2[idx2] == s3[idx3])
            if (isInterleave(s1, s2, s3, memo, idx1, idx2 + 1))
                return ans = true;
        return ans = false;
    }
};

