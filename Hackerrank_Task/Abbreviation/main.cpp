// Problem description: https://www.hackerrank.com/challenges/abbr/problem

#include <stdio.h>
#include <unordered_set>
#include <string>
#include <ctype.h>
#include <iostream>
#include <vector>

using namespace std;

typedef unordered_set<char> dict;
typedef vector<int> vi;
typedef vector<vi> vvi;

bool ProcessString(string& s, const string& sub)
{
	dict d;
	string result;
	for (const auto& e : sub) d.insert(e);

	for (size_t i = 0; i < s.size(); ++i)
	{
		if (isupper(s[i]))
		{
			auto it = d.find(s[i]);
			if (it == end(d)) return false;
		}

		auto it = d.find(toupper(s[i]));

		if (it != end(d)) result.push_back(s[i]);
	}
	
	s = move(result);

	return true;
}

int IsMatch(const string s, const string& sub, int ps, int psub, vvi& M)
{
	if (ps == s.size() && psub >= sub.size())
		return 1;
	else if (ps == s.size() && psub < sub.size())
		return 0;

	int ans = -1;

	if (psub < sub.size()) ans = M[ps][psub];

	if (ans != -1)
		return ans;
	else
	{
		if (isupper(s[ps])) // if uppercase letter
		{
			if (s[ps] == sub[psub]) // if match advance both indices
				ans = IsMatch(s, sub, ps + 1, psub + 1, M);
			else
				ans = 0;
		}
		else // lower case: 1) advance only ps (skip small letter) 2) if upper case match advance both
		{
			ans = IsMatch(s, sub, ps + 1, psub, M); // skip letter
			
			if (ans == 0)
				if (sub[psub] == toupper(s[ps]))
					ans = IsMatch(s, sub, ps + 1, psub + 1, M);
		}
	}

	if (psub < sub.size()) M[ps][psub] = ans;

	return ans;
}

auto main() -> int
{	
	int queries; cin >> queries;
	
	for (int q = 0; q < queries; ++q)
	{
		string s; cin >> s;
		string sub; cin >> sub;

		bool result = ProcessString(s, sub);

		if (!result)
			printf("%s\n", "NO");
		else
		{
			vvi M(s.size(), vi(sub.size(), -1));
			IsMatch(s, sub, 0, 0, M);
			printf("%s\n", M[0][0] == 1 ? "YES" : "NO");	
		}

	}
}
