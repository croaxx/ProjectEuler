// Problem description: https://contest.yandex.ru/contest/18492
// (or see problem_description.html).

// Short description: A 2D labyrinth is encoded by the following ASCII symbols:
// "+" - system grid cell.
// "|" and "-" - vertical and horizontal wall, respectively.
// "." - inner cell of the labyrinth.
// Cells with both even indices are filled with "+", cells with both odd indices
// are filled with ".", cells with one odd and one even indices can be either
// ".", "|" or "-".
// Task: remove the minimum number of internal walls ("|" or "-" cells) in the
// labyrinth, so that all internal dot cells (".") become connected. Print the
// resulting labyrinth with the minimum number of removed walls. In case of
// non unique solutions, print any of the solution.

// Example 1:
// 2 3      Possible solution:
// +-+-+-+  ->  +-+-+-+
// |.|...|  ->  |.....|
// +-+-+-+  ->  +.+-+-+
// |.|...|  ->  |.....|
// +-+-+-+  ->  +-+-+-+

// Example 2:
// 3 4        Possible solution:
// +-+-+-+-+  ->  +-+-+-+-+
// |...|...|  ->  |.......|
// +-+-+-+-+  ->  +.+-+-+.+
// |.|.|...|  ->  |.|.....|
// +-+-+-+-+  ->  +-+.+-+-+
// |...|...|  ->  |.......|
// +-+-+-+-+  ->  +-+-+-+-+

// Solution: Initially, all the dots in the labyrinth form some number of
// connected components (or unions). In the Example 1 and 2 there are
// initially 4 and 7 such connected unions, respectively.
// As can be observed, removal of any internal wall can lead to two scenarios:
// a) two unconnected unions become connected (border wall)
// b) no new connections between unions are formed (internal union wall)
// In order to solve the problem we will need a data structure called UnionFind
// (or Disjoint set), which allows efficient merging of disconnected unions
// and finding if two cells belong to the same union. Both of these operations
// can be done in nearly constant time.
// First we perform breadth-first traversal of the labyrinth and build unions
// during this traversal. Afterwards, we remove walls one by one, until the
// number of union components becomes one, i.e. all cells belong to the same
// union and are thus connected.
// Time complexity: O(number of cells).
// Space complexity: O(number of cells).

#include <vector>
#include <stdio.h>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <queue>

using namespace std;

using pii = pair<int, int>;
struct pair_hash
{
    size_t operator()(const pii &p) const
    {
        return hash<int>{}(p.first) ^ hash<int>{}(p.second);
    }
};
using vi = vector<int>;
using vc = vector<char>;
using matrix = vector<vc>;
using hash_table = unordered_set<pii, pair_hash>;
using hash_dict = unordered_map<pii, int, pair_hash>;


class UnionFind
{
    /*
    This data structure is taken from the book
    `Competitive Programming 3` by S.Halim and F.Halim.
    */
private:
    vi p, rank;
    int count;
public:
    UnionFind(int N)
    {
        count = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }

    int find_set(int i) { return (p[i] == i) ? i : (p[i] = find_set(p[i])); }

    bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

    void union_set(int i, int j)
    {
        if (!is_same_set(i, j))
        {
            int x = find_set(i), y = find_set(j);
            if (rank[x] > rank[y])
                p[y] = x;
            else
            {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
            --count;
        }
    }

    int get_unions_count() const { return count; }
};

void bfs(const matrix& matrix_2d,
         pii start_cell,
         hash_table& unvisited,
         const hash_dict& dot_cells,
         UnionFind& uf)
{
    /*
    Perform breadth-first search traversal and put the traversed cells into
    the same union component.
    */
    int union_idx = dot_cells.find(start_cell)->second;
    unvisited.erase(unvisited.find(start_cell));
    queue<pii> q;
    q.push(start_cell);
    while (!q.empty())
    {
        start_cell = q.front();
        q.pop();
        for (const auto &move : {pii(+1, 0), pii(-1, 0), pii(0, +1), pii(0, -1)})
        {
            pii next_cell = pii(start_cell.first + move.first,
                                start_cell.second + move.second);
            char ch = matrix_2d[next_cell.first][next_cell.second];
            if (ch == '.' && unvisited.find(next_cell) != end(unvisited))
            {
                unvisited.erase(unvisited.find(next_cell));
                q.push(next_cell);
                int next_cell_idx = dot_cells.find(next_cell)->second;
                uf.union_set(union_idx, next_cell_idx);
            }
        }
    }
}

void read_process_input(matrix& matrix_2d,
                        hash_dict& dot_cells,
                        hash_table& wall_cells,
                        hash_table& unvisited)
{
    // Read the input and build hash tables of internal cells and walls.
    int n, m;
    cin >> n >> m;
    matrix_2d = move(matrix(2 * n + 1, vc(2 * m + 1)));
    int rows = matrix_2d.size();
    int cols = matrix_2d[0].size();
    int count = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            char ch; cin >> ch;
            matrix_2d[i][j] = ch;
            if (ch == '.')
            {
                unvisited.emplace(i, j);
                dot_cells.emplace(pii(i, j), count);
                ++count;
            }
            else if (ch != '+' && i > 0 && i < rows - 1 && j > 0 && j < cols - 1)
            {
                wall_cells.emplace(i, j);
            }
        }
    }
}

void try_remove_wall(matrix& matrix_2d,
                     pii wall,
                     const hash_dict& dot_cells,
                     UnionFind& uf)
{
    //Break the wall if it connects different unions.
    char ch = matrix_2d[wall.first][wall.second];
    pii p1, p2;
    if (ch == '|')
    {
        p1 = pii(wall.first, wall.second - 1);
        p2 = pii(wall.first, wall.second + 1);
    }
    else
    {
        p1 = pii(wall.first - 1, wall.second);
        p2 = pii(wall.first + 1, wall.second);
    }
    int p1_idx = dot_cells.find(p1)->second;
    int p2_idx = dot_cells.find(p2)->second;
    if (!uf.is_same_set(p1_idx, p2_idx))
    {
        uf.union_set(p1_idx, p2_idx);
        matrix_2d[wall.first][wall.second] = '.';
    }
}

void print_matrix(const matrix& matrix_2d)
{
    int const rows = matrix_2d.size();
    int const cols = matrix_2d[0].size();
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            printf("%c", matrix_2d[row][col]);
        }
        printf("\n");
    }
}

auto main() -> int
{
    /*
    Read the input and do preprocessing on the fly.
    Store internal cells (".") and walls ("|" or "-") in hash tables.
    Hash table dot_cells is used to map cell position (i, j) to a cell
    index. This is necessary for using UnionFind data structure.
    */
    matrix matrix_2d;
    hash_dict dot_cells;
    hash_table wall_cells, unvisited_cells;
    read_process_input(matrix_2d, dot_cells, wall_cells, unvisited_cells);
    UnionFind union_find(dot_cells.size());
    // Traverse all internal cells (".") and build connected unions.
    while (!unvisited_cells.empty())
    {
        auto cell = *begin(unvisited_cells);
        bfs(matrix_2d, cell, unvisited_cells, dot_cells, union_find);
    }
    // Break walls until the number of union components becomes one.
    // This means that all cells belong to the same union (cells are connected).
    while (union_find.get_unions_count() != 1)
    {
        auto wall_it = begin(wall_cells);
        try_remove_wall(matrix_2d, *wall_it, dot_cells, union_find);
        wall_cells.erase(wall_it);
    }
    print_matrix(matrix_2d);
    return 0;
}

