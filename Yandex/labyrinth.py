# Problem description: https://contest.yandex.ru/contest/18492
# (or see problem_description.html).

# Short description: A 2D labyrinth is encoded by the following ASCII symbols:
# "+" - system grid cell.
# "|" and "-" - vertical and horizontal wall, respectively.
# "." - inner cell of the labyrinth.
# Cells with both even indices are filled with "+", cells with both odd indices
# are filled with ".", cells with one odd and one even indices can be either
# ".", "|" or "-".
# Task: remove the minimum number of internal walls ("|" or "-" cells) in the
# labyrinth, so that all internal dot cells (".") become connected. Print the
# resulting labyrinth with the minimum number of removed walls. In case of
# non unique solutions, print any of the solution.

# Example 1:
# 2 3      Possible solution:
# +-+-+-+  ->  +-+-+-+
# |.|...|  ->  |.....|
# +-+-+-+  ->  +.+-+-+
# |.|...|  ->  |.....|
# +-+-+-+  ->  +-+-+-+

# Example 2:
# 3 4        Possible solution:
# +-+-+-+-+  ->  +-+-+-+-+
# |...|...|  ->  |.......|
# +-+-+-+-+  ->  +.+-+-+.+
# |.|.|...|  ->  |.|.....|
# +-+-+-+-+  ->  +-+.+-+-+
# |...|...|  ->  |.......|
# +-+-+-+-+  ->  +-+-+-+-+

# Solution: Initially, all the dots in the labyrinth form some number of
# connected components (or unions). In the Example 1 and 2 there are
# initially 4 and 7 such connected unions, respectively.
# As can be observed, removal of any internal wall can lead to two scenarios:
# a) two unconnected unions become connected (border wall)
# b) no new connections between unions are formed (internal union wall)
# In order to solve the problem we will need a data structure called UnionFind
# (or Disjoint set), which allows efficient merging of disconnected unions
# and finding if two cells belong to the same union. Both of these operations
# can be done in nearly constant time.
# First we perform breadth-first traversal of the labyrinth and build unions
# during this traversal. Afterwards, we remove walls one by one, until the
# number of union components becomes one, i.e. all cells belong to the same
# union and are thus connected.
# Time complexity: O(number of cells).
# Space complexity: O(number of cells).

from typing import Dict, Tuple, List, Set

pii = Tuple[int, int]


class UnionFind:
    """
    This data structure is transpiled from the C++ source code, which is taken
    from the book `Competitive Programming 3` by S.Halim and F.Halim.
    """

    def __init__(self, n: int) -> None:
        self.n = n
        self.rank = [0] * n
        self.p = [i for i in range(n)]

    def find_set(self, i: int) -> int:
        if self.p[i] == i:
            return i
        self.p[i] = self.find_set(self.p[i])
        return self.p[i]

    def is_same_set(self, i: int, j: int) -> bool:
        return self.find_set(i) == self.find_set(j)

    def union_set(self, i: int, j: int) -> None:
        if not self.is_same_set(i, j):
            x = self.find_set(i)
            y = self.find_set(j)
            if self.rank[x] > self.rank[y]:
                self.p[y] = x
            else:
                self.p[x] = y
                if self.rank[x] == self.rank[y]:
                    self.rank[y] += 1
            self.n -= 1


def try_remove_wall(matrix_2d: List[List[str]],
                    wall: pii,
                    dot_cells: Dict[pii, int],
                    union_find: UnionFind) -> None:
    """Break the wall if it connects different unions."""
    char = matrix_2d[wall[0]][wall[1]]
    if char == '|':
        p1, p2 = (wall[0], wall[1] - 1), (wall[0], wall[1] + 1)
    else:
        p1, p2 = (wall[0] - 1, wall[1]), (wall[0] + 1, wall[1])
    if not union_find.is_same_set(dot_cells[p1], dot_cells[p2]):
        union_find.union_set(dot_cells[p1], dot_cells[p2])
        matrix_2d[wall[0]][wall[1]] = "."


def bfs(matrix_2d: List[List[str]],
        start_cell: pii,
        unvisited_cells: Set[pii],
        dot_cells: Dict[pii, int],
        union_find: UnionFind) -> None:
    """
    Perform breadth-first search traversal and put the traversed cells into
    the same union component.
    """
    unvisited_cells.remove(start_cell)
    queue = [start_cell]
    while queue:
        start_cell = queue.pop()
        for move in [(+1, 0), (-1, 0), (0, +1), (0, -1)]:
            next_cell = (start_cell[0] + move[0], start_cell[1] + move[1])
            char = matrix_2d[next_cell[0]][next_cell[1]]
            if char == '.' and next_cell in unvisited_cells:
                unvisited_cells.remove(next_cell)
                queue.append(next_cell)
                union_find.union_set(dot_cells[next_cell],
                                     dot_cells[start_cell])


def read_process_input() ->\
        Tuple[List[List[str]], Dict[pii, int], Set[pii], Set[pii]]:
    """Read the input and build hash tables of internal cells and walls."""
    rows, cols = map(lambda x: 2 * int(x) + 1, input().split(' '))
    dot_cells, wall_cells, unvisited_cells = dict(), set(), set()
    matrix_2d = [[""] * cols for _ in range(rows)]
    dot_cells_count = 0
    for row in range(rows):
        line = list(map(str, input()))
        for col in range(cols):
            char = line[col]
            matrix_2d[row][col] = line[col]
            if char == ".":
                dot_cells[(row, col)] = dot_cells_count
                unvisited_cells.add((row, col))
                dot_cells_count += 1
            elif char != "+" and 0 < row < rows - 1 and 0 < col < cols - 1:
                wall_cells.add((row, col))
    return matrix_2d, dot_cells, wall_cells, unvisited_cells


def main() -> None:
    # Read the input and do preprocessing on the fly.
    # Store internal cells (".") and walls ("|" or "-") in hash tables.
    # Hash table dot_cells is used to map cell position (i, j) to a cell
    # index. This is necessary for using UnionFind data structure.
    matrix_2d, dot_cells, wall_cells, unvisited_cells = read_process_input()
    unions_count = len(dot_cells)
    union_find = UnionFind(unions_count)
    # Traverse all internal cells (".") and build connected unions.
    while unvisited_cells:
        cell = next(iter(unvisited_cells))
        bfs(matrix_2d, cell, unvisited_cells, dot_cells, union_find)
    # Break walls until the number of union components becomes one.
    # This means that all cells belong to the same union (cells are connected).
    while union_find.n != 1:
        wall = next(iter(wall_cells))
        try_remove_wall(matrix_2d, wall, dot_cells, union_find)
        wall_cells.remove(wall)
    print('\n'.join(map(''.join, matrix_2d)))


if __name__ == "__main__":
    main()
