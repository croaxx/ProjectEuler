// Problem description: https://leetcode.com/problems/wildcard-matching/

// Time complexity: O(nm)
// Space complexity : O(nm) - 2D memoization table
// Two solutions:
// 1) Faster, but less memory efficient
// 2) Slower, but more memory efficient

#include <vector>
#include <string>

using namespace std;

// recursive solution
// fast, but requires additional memory due to stack allocation
class Solution
{
private:
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    int isMatch(int idx_s, int idx_p, const string& s, const string& p, vvi& memo)
    {
        int& ans = memo[idx_s][idx_p];
        
        if (ans != -1) return ans;        
        
        if (idx_s == s.size())
        {
            if (idx_p == p.size()) return ans = 1;
            else if (p[idx_p] == '*') return ans = isMatch(idx_s, idx_p + 1, s, p, memo);
            else return ans = 0;
        }
        else if (idx_p == p.size()) return ans = 0;
        
        if (p[idx_p] == '?') return ans = isMatch(idx_s + 1, idx_p + 1, s, p, memo);
        else if (p[idx_p] == '*')
        {
            bool result = 
            isMatch(idx_s, idx_p + 1, s, p, memo) == 1 ||
            isMatch(idx_s + 1, idx_p + 1, s, p, memo) == 1 ||
            isMatch(idx_s + 1, idx_p, s, p, memo) == 1;

            if (result) return ans = 1;
            else return ans = 0;
        }
        else if (p[idx_p] == s[idx_s]) return ans = isMatch(idx_s + 1, idx_p + 1, s, p, memo);
        else return ans = 0;            
    }
    
    bool isMatch(string s, string p)
    {
        vvi memo(s.size() + 1, vi(p.size() + 1, -1));
        return bool(isMatch(0, 0, s, p, memo));
    }
};

// non recursive solution
// slower, but more efficient memory usage
class Solution2
{
private:
    using vb = vector<bool>;
    using vvb = vector<vb>;
public:
    bool isMatch(string s, string p)
    {
        size_t m = s.size(), n = p.size();
        vvb B(m + 1, vb(n + 1, false));
        B[0][0] = true;
        for (size_t j = 1; j < n + 1; ++j)
            if (p[j-1] != '*') B[0][j] = false;
            else B[0][j] = B[0][j-1];

        for (size_t i = 1; i < m + 1; ++i)
        {
            for (size_t j = 1; j < n + 1; ++j)
            {
                if (p[j-1] == s[i-1])
                    B[i][j] = B[i-1][j-1];
                else if (p[j-1] != s[i-1] && p[j-1] != '?' && p[j-1] != '*')
                    B[i][j] = false;
                else if (p[j-1] == '?')
                    B[i][j] = B[i-1][j-1];
                else
                {
                    bool is_any = false;
                    for (int k = 0; k < i + 1; ++k)
                    {
                        if (B[i-k][j-1] == true)
                        {
                            is_any = true;
                            break;
                        }
                    }
                    if (is_any) B[i][j] = true;
                    else B[i][j] = false;
                }
            }
        }
        return B[m][n];
    }
};
