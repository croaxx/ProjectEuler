#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>

using namespace std;

typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef unordered_multimap<int, pii> map;
typedef unordered_set<int> seti;
typedef stack<pii> stackii;

class DataReader
{
private:
	map s_;
	seti rows_;
	ull m_;
	ull n_;
public:
	DataReader() {};

	void read()
	{
		int k; cin >> n_ >> m_ >> k;
		for (int i = 0; i < k; ++i)
		{
			int r, c1, c2; cin >> r >> c1 >> c2;
			pii interval = make_pair(c1, c2);
			s_.insert(make_pair(r, interval));
			rows_.insert(r);
		}
	}

	map& get_data()
	{
		return s_;
	}

	seti& get_keys()
	{
		return rows_;
	}

	ull get_total_elements()
	{
		return m_ * n_;
	}
};

class Processor
{
private:
	ull elem_count = 0;
	map s_;
	seti keys_;
public:
	Processor(map&& s, seti keys): s_(move(s)), keys_(move(keys)) {};

	void proccess_rows()
	{
		for (const auto& k : keys_)
		{
			proccess_row(k);
		}
	}

	void proccess_row(int row)
	{
		auto it = s_.equal_range(row);
		vpii intervals;
		for (auto it1 = it.first; it1 != it.second; ++it1)
		{
			intervals.push_back(make_pair(it1->second.first, it1->second.second));
		}
		sort(begin(intervals), end(intervals), [](const pii& a, const pii& b) 
		{
			if (a.first == b.first) return a.second < b.second;
			return a.first < b.first;
		});
		
		// create stack of intervals
		stackii ranges;
		if (!intervals.empty())	{ ranges.push(intervals[0]); }
		for (auto it1 = ++begin(intervals); it1 != end(intervals); ++it1)
		{
			auto& top = ranges.top();
			if (it1->first <= top.second && it1->first >= top.first)
				top.second = std::max(it1->second, top.second);
			else // push the interval if it doesn't overlap with the top element
				ranges.push(*it1);
		}
		while (!ranges.empty())
		{
			auto top = ranges.top(); ranges.pop();
			elem_count += top.second - top.first + 1;
		}
	}

	ull get_number_of_occupied()
	{
		return elem_count;
	}
};

auto main() -> int
{
	DataReader reader;
	reader.read();
	Processor processor(move(reader.get_data()), move(reader.get_keys()));
	processor.proccess_rows();
	printf("%llu", reader.get_total_elements() - processor.get_number_of_occupied());
}
