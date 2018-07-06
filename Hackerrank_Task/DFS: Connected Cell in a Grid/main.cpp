// Problem definition : https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/problem

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <unordered_map>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<pair<int, int>> vpii;

int dfs(int i, int j, const vvb& grid, 
	vvb& visited, int count, const vpii& moves)
{
    if (i < 0 ||  i >= grid.size() || j < 0 || j >= grid[0].size() || visited[i][j] || !grid[i][j])
        return 0;

    visited[i][j] = true;
    count++;
    for (const auto& e : moves)
        count += dfs(i+e.first, j+e.second, grid, visited, 0, moves);
    return count;
}

int largest_region(const vvb& grid, vvb& visited)
{
    int max_region = -1;
    vpii moves{make_pair(-1, -1), make_pair(-1, 0),
               make_pair(-1, +1), make_pair(0, +1),
               make_pair(+1, +1), make_pair(+1, 0),
               make_pair(+1, -1), make_pair(0, -1)};
    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[0].size(); ++j)
                max_region = max(max_region, dfs(i, j, grid, visited, 0, moves));
    return max_region;
}

int main()
{
    int n, m; cin >> n >> m;
    vvb grid(n, vb(m, false));
    vvb visited = grid;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            bool v; cin >> v;
            if (v) grid[i][j] = true;
        }
    }
    printf("%d", largest_region(grid, visited));
}
