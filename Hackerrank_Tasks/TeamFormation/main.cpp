// Problem definition: https://www.hackerrank.com/challenges/team-formation/problem
// Time complexity: O(NlogN), space complexity: O(N)

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

using vi = vector<int>;
using intVi = pair<int, vi>;
using mapIntVi = unordered_map<int, vi>;

class MapIntHeap
{
private:
    mapIntVi m; // map: (key - int, value - heap as vector<int>)
public:
    bool key_exists(int key)
    {
        return m.find(key) != end(m);
    }

    int get_min_for_key(int key)
    {
        return m.find(key)->second.front();
    }

    void pop_heap_for_key(int key)
    {
        auto& heap = m.find(key)->second;
        pop_heap(begin(heap), end(heap), greater<int>());
        heap.pop_back();
        if (heap.empty()) m.erase(key);
    }

    void insert(int key, int value)
    {
        m.emplace(key, vi { value });
    }

    void push_heap_for_key(int key, int value)
    {
        auto& heap = m.find(key)->second;
        heap.push_back(value);
        push_heap(begin(heap), end(heap), greater<int>());
    }

    int min_value()
    {
        auto it = min_element(begin(m), end(m), [](const intVi& lhs, const intVi& rhs)
        {
            return lhs.second.front() < rhs.second.front();
        });
        return it->second.front();
    }
};

int find_min_team(vi& skills)
{
    sort(begin(skills), end(skills));
    MapIntHeap map;

    for (const auto& n : skills)
    {
        int team_size;
        if (!map.key_exists(n-1)) // form a new team
        {
            team_size = 0;
        }
        else
        {
            team_size = map.get_min_for_key(n - 1);
            map.pop_heap_for_key(n-1);
        }

        if (!map.key_exists(n))
        {
            map.insert(n, team_size + 1);
        }
        else
        {
            map.push_heap_for_key(n, team_size + 1);
        }
    }

    return map.min_value();
}

auto main() -> int
{
    int tests; cin >> tests;
    for (int test = 0; test < tests; ++test)
    {
        int n; cin >> n;
        // check to adhere to a strange condition in the problem definition
        if (n == 0)
        {
             printf("%d\n", 0);
             continue;
        }

        vi skills(n);
        for (int i = 0; i < n; ++i) cin >> skills[i];

        int size = find_min_team(skills);
        printf("%d\n", size);
    }
}