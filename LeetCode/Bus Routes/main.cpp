// Problem description: https://leetcode.com/problems/bus-routes/
// Time complexity: O(|V|+|E|), |V| - number of vertices, |E| - number of edges
// Space complexity: O(|V|+|E|) storing the graph

class Solution
{
private:
	using mapii = unordered_map<int, int>;
	using graph = unordered_map<int, mapii>; // map: vetrexIndex -> map<busIndex, nextVertex>
	using vi = vector<int>;
	using vvi = vector<vi>;

	graph g;

	void buildGraph(const vvi& routes)
	{
		for (int bus = 0; bus < (int)routes.size(); ++bus)
		{
			for (int i = 0; i < (int)routes[bus].size(); ++i)
			{
				int fromVertex = routes[bus][i];
				int toVertex = i == routes[bus].size() - 1 ? routes[bus][0] : routes[bus][i + 1];
				if (g.find(fromVertex) == end(g)) g.emplace(fromVertex, mapii{});
				g[fromVertex].emplace(bus, toVertex);
			}
		}
	}

	int traverse(int S, int T)
	{
		if (S == T) return 0;
		int count = 1;
		unordered_set<int> visited{S}, buses;
		queue<int> q; q.push(S);

		while (!q.empty())
		{
			queue<int> q_tmp;
			while (!q.empty())
			{
				int startVertex = q.front(); q.pop();
				for (const auto& e : g[startVertex]) // traverse all bus lines going through this vertex
				{
					int busIdx = e.first;
					int nextVertex = e.second;

					if (buses.find(busIdx) != end(buses)) continue;
					else buses.emplace(busIdx); // mark this bus line as traversed

					do
					{
						if (nextVertex == T) return count;
						if (visited.find(nextVertex) == end(visited))
						{
							q_tmp.push(nextVertex);
							visited.emplace(nextVertex);
						}
						nextVertex = g[nextVertex][busIdx];
					} while (nextVertex != startVertex); // traverse all stations of this bus line
				}
			}
			++count;
			q = move(q_tmp);
		}
		return -1;
	}

public:
	int numBusesToDestination(const vvi& routes, int S, int T)
	{
		buildGraph(routes);
		return traverse(S, T);
	}
};
