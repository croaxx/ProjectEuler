#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <numeric>

using namespace std;
using vi = vector<int>;

class DisjointSet
{
private:
	vi communitySizes;
	vi parent;
	vi rank;
public:
	DisjointSet(int n)
	{
		parent.resize(n, 0);
		communitySizes.resize(n, 1);
		iota(begin(parent), end(parent), 0);
		rank.resize(n);
	}

	int findSet(int i)
	{
		return (parent[i] == i) ? i : (parent[i] = findSet(parent[i]));
	}

	int CommunitySize(int person)
	{
		return communitySizes[findSet(person)];
	}

	bool isSameSet(int i, int j)
	{
		return findSet(i) == findSet(j);
	}

	void UnionSet(int i, int j)
	{
		if (!isSameSet(i, j))
		{
			int x = findSet(i);
			int y = findSet(j);

			if (rank[x] > rank[y])
			{
				parent[y] = x;
				communitySizes[x] += communitySizes[y];
				communitySizes[y] = 0;
			}
			else
			{
				parent[x] = y;
				communitySizes[y] += communitySizes[x];
				communitySizes[x] = 0;

				if (rank[x] == rank[y])
					++rank[y];
			}
		}
	}
	void printRanks()
	{
		for (const auto& e : rank)
			printf("%d ", e);
	}
};

int main()
{
	int N, q;
	cin >> N >> q;

	DisjointSet comminity(N);

	for (int qi = 0; qi < q; ++qi)
	{
		char v;
		cin >> v;

		if (v == 'Q')
		{
			int n;
			cin >> n;
			printf("%d\n", comminity.CommunitySize(n - 1));
		}
		else if (v == 'M')
		{
			int i, j;
			cin >> i >> j;
			comminity.UnionSet(i - 1, j - 1);
		}
	}

	return 0;
}
