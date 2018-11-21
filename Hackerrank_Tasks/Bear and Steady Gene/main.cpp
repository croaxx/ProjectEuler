// Problem : https://www.hackerrank.com/challenges/bear-and-steady-gene/problem

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, int> map;

pair<map, bool> compute_balance_map(const string& s)
{
    map m;
    for (const auto& e: s) { ++m[e]; }
    int repetitions = s.size() / 4;
    bool isBalanced = true;
    for (auto& e: m)
    {
        if (e.second != repetitions) { isBalanced = false; }
        e.second -= repetitions;
    }
    map m_processed;
    for (auto& e: m)
        if (e.second > 0)
            m_processed[e.first] = e.second;
    return make_pair(m_processed, isBalanced);
}

int compare_maps(const map& m, const map& balance_map)
{
    for (const auto& e: balance_map)
    {
        auto it = m.find(e.first);
        if (it == end(m)) { return -1; }
        if (e.second > it->second) { return -1; }
    }
    return 1;
}

int compute_min_length(const string& s, const map& balance_map)
{
    map map_current;
    int start = 1, end = 0, balance;
    unsigned min_length = ~0;
    map_current[s[end]]++;
    while (start < s.size() && end < s.size())
    {
        while (start < s.size())
        {
            map_current[s[start]]++;
            balance = compare_maps(map_current, balance_map);
            start++;
            if (balance == 1) { break; }
        }
        while (end < start)
        {
            min_length = std::min(min_length, (unsigned)(start - end));
            map_current[s[end]]--;
            balance = compare_maps(map_current, balance_map);
            end++;
            if (balance == -1) { break; }
        }
    }
    return min_length;
}

int main()
{
    int n; cin >> n;
    string s; cin >> s;
    pair<map, bool> balance_map = compute_balance_map(s);
    if (balance_map.second) { printf("%d\n", 0); }
    else
    {
        int min_length = compute_min_length(s, balance_map.first);
        printf("%d\n", min_length);
    }
    return 0;
}
