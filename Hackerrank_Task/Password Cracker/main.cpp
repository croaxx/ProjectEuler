// Problem description: https://www.hackerrank.com/challenges/password-cracker/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stack>
#include <utility>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<string> vecstr;
typedef unordered_map<int, vpii> maptable;
typedef unordered_set<string> dict;


maptable FindWordsOccurencesInPassword(const string& passw, const vecstr& words)
{
    maptable t;
    for (int pos = 0; pos < passw.size(); ++pos)
    {
        for (int idx = 0; idx < words.size(); ++idx)
        {
            if (passw.compare(pos, words[idx].size(), words[idx]) == 0)
            {
                auto it = t.find(pos);
                if (it == end(t))
                    t.insert(make_pair(pos, vpii { make_pair(idx, words[idx].size()) }));
                else
                    (it->second).push_back(make_pair(idx, words[idx].size()));
            }
        }
    }

    return t;
}

void SearchPasswConcatinations(const string& passw, vi& pos, const maptable& t, vi& parents)
{
	if (parents.back() != -1) return;

	vi next_pos;
	for (auto& p : pos)
	{
		auto it = t.find(p);

		if (it != end(t))
		{
			auto matches = (*it).second;

			for (int i = 0; i < matches.size(); ++i)
			{
				int end_word = p + matches[i].second - 1;

				if (parents[end_word] == -1)
				{
					parents[end_word] = p;
					next_pos.push_back(end_word + 1);
				}
			}
		}
	}

	if (!next_pos.empty())
		SearchPasswConcatinations(passw, next_pos, t, parents);
}

void PrintSequence(const string& passw, const vi& parents)
{
	vecstr words;
	int start = parents.back();
	int end = parents.size() - 1;

	while(start >= 0)
	{
		words.push_back(passw.substr(start, end - start + 1));
		end = start - 1;

		if (end < 0)
			start = -1;
		else
			start = parents[end];
	}

    for (auto it = rbegin(words); it != rend(words); it++)
    	printf("%s ", (*(it)).c_str());

    printf("\n");
}

int main()
{
    int queries; cin >> queries;
    for (int q = 0; q < queries; ++q)
    {
        int n; cin >> n;
        vecstr words(n);
        for (int i = 0; i < n; ++i) cin >> words[i];

        string passw; cin >> passw;
        maptable t = FindWordsOccurencesInPassword(passw, words);

        vi parents(passw.size(), -1);
        vi positions{0};
        SearchPasswConcatinations(passw, positions, t, parents);

        if (parents.back() == -1) printf("WRONG PASSWORD\n");
        else PrintSequence(passw, parents);
    }

    return 0;
}
