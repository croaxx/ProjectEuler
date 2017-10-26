// Problem description: https://www.hackerrank.com/challenges/insertion-sort/problem

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef long long lli;

auto merge(vi& a, vi& tmp, int leftPos,	int rightPos,
	int rightEnd, lli& count) -> void
{
	int rightStart = rightPos;
	int leftPosStart = leftPos;
	int leftEnd = rightPos - 1;
	int position = 0;

	while (true)
	{
		if (a[leftPos] > a[rightPos])
		{
			tmp[position++] = a[rightPos++];
		}
		else
		{
			count += rightPos - rightStart;
			tmp[position++] = a[leftPos++];
		}

		if (leftPos > leftEnd)
		{
			for (int i = rightPos; i <= rightEnd; ++i)
			{
				tmp[position++] = a[i];
			}

			break;
		}
		else if (rightPos > rightEnd)
		{
			for (int i = leftPos; i <= leftEnd; ++i)
			{
				count += rightPos - rightStart;
				tmp[position++] = a[i];
			}

			break;
		}
	}

	// copy the tmp array back to a
	for (int i = 0; i < position; ++i)
		a[leftPosStart+i] = tmp[i];

}

auto merge_sort(vi& array, vi& tmpArray,
	int left, int right, lli& count) -> void
{
	if (left < right)
	{
		int center = (left + right) / 2;
		merge_sort(array, tmpArray, left, center, count);
		merge_sort(array, tmpArray, center + 1, right, count);
		merge(array, tmpArray, left, center + 1, right, count);
	}
}

auto merge_sort(vi& array, lli& count) -> void
{
	vi tmp(array.size());
	merge_sort(array, tmp, 0, array.size() - 1, count);
}

auto main() -> int
{
 	int q;
	cin >> q;

	for (int qi = 0; qi < q; ++qi)
	{
		int n; cin >> n;

		vi v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];

		lli moves = 0;
		merge_sort(v, moves);

		printf("%lld\n", moves);
	}
}

