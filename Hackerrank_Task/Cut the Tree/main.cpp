// Problem definition : https://www.hackerrank.com/challenges/cut-the-tree/problem

#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<pii> vpii;

struct Vertex
{
	int value = 0;
	vi neighbs;
	ull sum = 0;
};

ull compute_tree_sums(Vertex& v, vector<Vertex>& vertices)
{
	v.sum += (ull)v.value;
	for (auto& n : v.neighbs)
	{
		if (vertices[n].sum == 0) { v.sum += compute_tree_sums(vertices[n], vertices); }
	}
	return v.sum;
}

auto main() -> int
{
	int n; cin >> n;
	vector<Vertex> vertices(n);
	for (int i = 0; i < n; ++i) { cin >> vertices[i].value; }
	vpii edges(n - 1); // pair from vertex - to vertex
	for (int i = 0; i < n - 1; ++i)
	{
		int a, b; cin >> a >> b;
		edges[i] = make_pair(a - 1, b - 1);
		vertices[a-1].neighbs.push_back(b - 1);
		vertices[b-1].neighbs.push_back(a - 1);
	}
	compute_tree_sums(vertices[0], vertices);
	ull diff_min = ~0;
	for (auto const& e: edges)
	{
		ull sum1 = vertices[e.first].sum;
		ull sum2 = vertices[e.second].sum;
		if (sum1 > sum2) { sum1 = vertices[0].sum - sum2; }
		else { sum2 = vertices[0].sum - sum1; }
		ull diff = sum1 - sum2;
		if (sum2 > sum1) { diff = sum2 - sum1; }
		diff_min = std::min(diff, diff_min);
	}
	printf("%llu", diff_min);
}
