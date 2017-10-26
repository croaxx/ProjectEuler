// Problem description: https://www.hackerrank.com/challenges/dijkstrashortreach/problem

#include <iostream>
#include <vector>
#include <queue>
#include <limits>


using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long lli;
typedef pair<lli, int> pllii;
typedef vector<lli> vlli;

const lli INF = numeric_limits<lli>::max() / 4;

vlli Dijkstra(vvi& adj, vvi& cost, int s)
{
	vlli vd( adj.size(), INF ); vd[s] = 0;
	priority_queue<pllii, vector<pllii>, greater<pair<lli, int>>> vdQueue;

	vdQueue.push(make_pair( 0, s));
	int vNext;
	lli vNextDist;

	while (!vdQueue.empty())
	{
		vNext = vdQueue.top().second;
		vNextDist = vdQueue.top().first;
		vdQueue.pop();

		if (vNextDist > vd[vNext])
			continue;

		for (int i = 0; i < (int)adj[vNext].size(); ++i)
		{
			int w = adj[vNext][i];
			lli distTmp = vNextDist + (lli)cost[vNext][i];

			if (distTmp < vd[w])
			{
				vd[w] = distTmp;
				vdQueue.push( make_pair( distTmp, w ) );
			}
		}
	}

    return vd;
};

auto main() -> int
{
	int tests; cin >> tests;

	for (int t = 0; t < tests; ++t)
	{
		int n, m; cin >> n >> m;

		vvi adj(n, vi());
		vvi cost(n, vi());

		for (int i = 0; i < m; i++)
		{
			int x, y, w;
			cin >> x >> y >> w;

			adj[x - 1].push_back(y - 1);
			cost[x - 1].push_back(w);

			adj[y - 1].push_back(x - 1);
			cost[y - 1].push_back(w);
		}

		int s; cin >> s;

		auto distances = Dijkstra(adj, cost, s - 1);

		for (int i = 0; i < n; ++i)
		{
			if (distances[i] == INF)
				distances[i] = -1;

			if (i != s - 1)
				printf("%lld ", distances[i]);
		}
		printf("\n");
	}
}

