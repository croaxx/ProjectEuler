// Problem definition: https://www.hackerrank.com/challenges/reverse-shuffle-merge/problem
// Solution: greedy algorithm with backtracking

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>

using namespace std;

using vi = vector<int>;
using mapii = map<int, int>;

int assign_next_letter(const string& s, int start_idx, mapii& letters, vi& chars_left)
{
    int idx_min = -1, current = start_idx;
    int char_min = begin(letters)->first;

    for (; current >= 0; --current)
    {
        int ch = s[current] - 'a';
        int left = --chars_left[ch];

        if (ch == char_min)
        {
            idx_min = current;
            break;
        }

        auto it = letters.find(ch);
        if (it != end(letters))
        {
            idx_min = idx_min == -1 ?
                      current : ch < s[idx_min] - 'a' ?
                      current : idx_min;

            if (left < it->second) break;
        }
    }

    for (; current <= idx_min; ++current)
        ++chars_left[s[current]-'a'];

    int ch = s[idx_min] - 'a';
    --chars_left[ch];

    if (--letters[ch] == 0)
        letters.erase(letters.find(ch));

    return idx_min;
}

string find_min_string(const string& s)
{
    string w;
    mapii letters;
    int N = 26, idx = s.size() - 1;

    vi chars_left(N, 0);

    for (const auto& ch : s)
        ++chars_left[ch-'a'];

    for (int i = 0; i < N; ++i)
    {
        int count = chars_left[i];
        if (count != 0)
        {
            letters.emplace(i, count / 2);
        }
    }

    while (!letters.empty())
    {
        idx = assign_next_letter(s, idx, letters, chars_left);
        w.push_back(s[idx]);
        --idx;
    }

    return w;
}

int main()
{
    string s, w; cin >> s;

    if (s.size() == 1) w = s;
    else w = find_min_string(s);

    printf("%s", w.c_str());
    return 0;
}
