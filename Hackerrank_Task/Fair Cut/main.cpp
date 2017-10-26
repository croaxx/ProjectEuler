// Problem description: https://www.hackerrank.com/challenges/fair-cut/problem

#include <stdio.h>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

typedef list<int> li;
typedef unsigned long long ull;

auto main() -> int
{
	int n, k; cin >> n; cin >> k;

	li J;
	for (int i = 0; i < n; ++i)
	{
		int number; cin >> number;
		J.push_back(number);
	}

	J.sort();

	li I;
	auto it = begin(J);

    if (k > n/2) k = n - k;

	advance(it, n/2 - k);

	for (int i = 0; i < k;++i)
	{
		I.push_back(*it);
		auto it_next = it;
		advance(it_next, 2);
		J.erase(it);
		it = it_next;
	}

	ull min_unfairness = 0;

	for (auto it1 = begin(I); it1 != end(I); ++it1)
	{
		for (auto it2 = begin(J); it2 != end(J); ++it2)
		{
			min_unfairness += fabs(*it1 - (*it2));
		}
	}

	printf("%llu", min_unfairness);
}

