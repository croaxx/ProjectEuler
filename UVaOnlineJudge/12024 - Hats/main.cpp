// Problem definition : https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3175

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
typedef vector<lli> vi;

lli factorial(lli n)
{
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

lli combinations(lli n, vi& A)
{
	if (n <= 1) A[n] = 0;
	else if (n == 2)  A[n] = 1;
	else if (A[n-1] != -1) A[n] = (n - 1) * (A[n-1] + A[n-2]);
	else A[n] = (n - 1) * (combinations(n - 1, A) + combinations(n - 2, A));
	return A[n];
}

auto main() -> int
{
	int tests;
	cin >> tests;
	for (int i = 0; i < tests; ++i)
	{
		lli hats;
		cin >> hats;
		vi A(hats + 1, -1);
		printf("%lld/%lld\n", combinations(hats, A), factorial(hats));
	}
	return 0;
}
