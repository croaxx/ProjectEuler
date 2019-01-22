// Problem description: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1557
// Time complexity: O(NDM), space: O(NDM)
// Top-bottom DP

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

using lli = long long int;
using vi = vector<lli>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int mod(int a, int b) {	return (a % b + b) % b; }

lli count_sets(int idx, int left, int sum, const vi& A, int D, vvvi& memo)
{
	if (left == 0)
	{
		if (sum % D == 0) return 1;
		else return 0;
	}
	else if (idx == A.size()) return 0;

	lli& ans = memo[idx][left][mod(sum, D)];
	if (ans != -1) return ans;

	return ans = count_sets(idx + 1, left - 1, mod(sum + A[idx], D), A, D, memo) +
		     count_sets(idx + 1, left, mod(sum, D), A, D, memo);
}

auto main() -> int
{
	int N, Q, set_num = 1;
	cin >> N >> Q;
	while (N != 0 && Q != 0)
	{
		vi A(N);
		for (int i = 0; i < N; ++i) cin >> A[i];
		printf("SET %d:\n", set_num++);
		for (int q = 0; q < Q; ++q)
		{
			int D, M; cin >> D >> M;
			vvvi memo(N + 1, vvi(M + 1, vi(D + 1, -1)));
			lli count = count_sets(0, M, 0, A, D, memo);
			printf("QUERY %d: %lld\n", q + 1, count);
		}
		cin >> N >> Q;
	}
}
