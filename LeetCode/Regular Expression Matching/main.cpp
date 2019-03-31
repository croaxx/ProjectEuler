// Problem description: https://leetcode.com/problems/regular-expression-matching

// Time complexity: O(nm)
// Space complexity: O(nm)

#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

class Solution
{
private:
    using vi = vector<int>;
    using vvi = vector<vi>;
public:
    bool isNextStar(const string &s, int idx)
    {
        return idx < s.size() - 1 && s[idx+1] == '*' ? true : false;
    }
    
    int isMatch(int idx_s, int idx_p, const string& s, const string& p, vvi& memo)
    {
        int& ans = memo[idx_s][idx_p];

        if (ans != -1) return ans;

        if (idx_s == s.size())
        {
            if (idx_p == p.size()) return ans = 1;
            else if (p[idx_p] != '*')
            {
                if (isNextStar(p, idx_p)) return ans = isMatch(idx_s, idx_p + 2, s, p, memo);
                else return ans = 0;
            }
            else return ans = 0;
        }
        else if (idx_p == p.size()) return ans = 0;
        
        if (p[idx_p] == '.' && !isNextStar(p, idx_p)) return ans = isMatch(idx_s + 1, idx_p + 1, s, p, memo);
        
        if (isNextStar(p, idx_p))
        {
            if (p[idx_p] == '.')
            {
                bool result =
                        isMatch(idx_s + 1, idx_p, s, p, memo) == 1 ||
                        isMatch(idx_s, idx_p + 2, s, p, memo) == 1;
                if (result) return ans = 1;
                else return ans = 0;
            }
            else
            {
                bool result =
                        isMatch(idx_s, idx_p + 2, s, p, memo) == 1 ||
                        s[idx_s] == p[idx_p] && isMatch(idx_s + 1, idx_p, s, p, memo) == 1 ||
                        s[idx_s] == p[idx_p] && isMatch(idx_s + 1, idx_p + 2, s, p, memo) == 1;

                if (result) return ans = 1;
                else return ans = 0;
            }
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
