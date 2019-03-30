// Problem description: https://leetcode.com/problems/minimum-window-substring/submissions/

// Time complexity: O(S+T) - one pass over the string S with expand and shrink windowing
// Space complexity: O(1) - dictionary of ASCII symbols + ints

#include <unordered_map>

using namespace std;

const int INF = INT32_MAX;

class Solution
{
private:
    using dict = unordered_map<char, int>;
    dict ds, dt;
    int mismatches, min_w, idx;

    void build_dict(const string& str)
    {
        for (const auto& ch : str) ++dt[ch];
    }

    int expandWindow(int L, int R, const string& s, const string& t)
    {
        while (mismatches > 0 && R != s.size())
        {
            char ch = s[++R];
            ++ds[ch];
            if (dt.find(ch) != end(dt) && dt[ch] >= ds[ch]) --mismatches;
        }
        return R;
    }

    int shrinkWindow(int L, int R, const string& s, const string& t)
    {
        if (mismatches != 0) return R;
        int len = R - L + 1;
        while (mismatches == 0 && L <= R)
        {
            if (mismatches == 0 && min_w > len)
            {
                min_w = len;
                idx = L;
            }
            char ch = s[L++];
            --ds[ch];
            if (dt.find(ch) != end(dt) && dt[ch] > ds[ch]) ++mismatches;
            --len;
        }
        return L;
    }

public:
    string minWindow(const string& s, const string& t)
    {
        build_dict(t);
        ds.clear();
        idx = 0; min_w = INF; mismatches = (int)t.size();
        int L = 0, R = -1;
        while (L < s.size())
        {
            R = expandWindow(L, R, s, t);
            L = shrinkWindow(L, R, s, t);
        }
        if (min_w != INF) return s.substr(idx, min_w);
        else return "";
    }
};
