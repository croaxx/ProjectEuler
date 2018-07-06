// Problem definition : https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/problem

#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef long long int lli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef queue<int> qi;

vvi read_graph()
{
	int n, m; cin >> n >> m;
	vvi graph(n);
	for (int i = 0; i < m; ++i)
	{
		int v, w; cin >> v >> w;
		graph[v - 1].push_back(w - 1);
		graph[w - 1].push_back(v - 1);
	}
	return move(graph);
}

vi bfs(const vvi& graph, int s)
{
	const int n = (int)graph.size();
	vi distances(n, -1); distances[s] = 0;
	vb visited(n, false);
	qi q; q.push(s);

	while (!q.empty())
	{
		int v = q.front(); q.pop();
		visited[v] = true;
		for (int i = 0; i < graph[v].size(); ++i)
		{
			int w = graph[v][i];
			if (!visited[w])
			{
				visited[w] = true;
				distances[w] = distances[v] + 1;
				q.push(w);
			}
		}
	}
	return distances;
}

void print_distances(const vi& distances)
{
	for (const auto& e : distances)
	{
		if (e == -1) printf("-1 ");
		else if (e != 0) printf("%lld ", (lli)6 * (lli)e);
	}
	printf("\n");
}

auto main() -> int
{
	int queries; cin >> queries;
	for (int q = 0; q < queries; ++q)
	{
		vvi graph = read_graph();
		int s; cin >> s; // start vertex
		vi distances = bfs(graph, --s); // vertex numbers start from 0
		print_distances(distances);
	}
}
