#include <boost/rational.hpp>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

template <typename T>
class Circuit
{
private:
	int N;
	T _capacitance;
	vector<set<T>> _capacitancesArrays;
	set<T> _uniqueCapacitances;
public:
	Circuit() = delete;

	explicit Circuit(const T& _cap) :_capacitance(_cap), N(1)
	{
		_capacitancesArrays.push_back(set<T> { _capacitance });
		_uniqueCapacitances.insert(begin(_capacitancesArrays[0]), end(_capacitancesArrays[0]));
	};

	auto AddCapacitorToCircuit()->void
	{
		N++;
		_capacitancesArrays.push_back(set<T> {});

		for (unsigned i = N - 1; i >= 1; i--)
		{
			unsigned j = N - i;

			for (const auto& m :_capacitancesArrays[j - 1])
			{
				for (const auto& n: _capacitancesArrays[i - 1])
				{
					_capacitancesArrays[N - 1].emplace(m + n);		  //consecutive connection
					_capacitancesArrays[N - 1].emplace(m*n / (m + n));//parallel connection
				}
			}
		}

		_uniqueCapacitances.insert(begin(_capacitancesArrays[N - 1]), end(_capacitancesArrays[N - 1]));
	}

	auto ShowUniqueCap() const -> size_t
	{
		return _uniqueCapacitances.size();
	}
};

auto main()->int
{
	const int N = 18;
	Circuit<boost::rational<unsigned>> capacitanceCircuits{ 1 };

	chrono::time_point<chrono::system_clock> start, end;
	for (unsigned i = 2; i <= N; i++)
	{
		start = system_clock::now();
		capacitanceCircuits.AddCapacitorToCircuit();
		end = system_clock::now();
		cout << "circuit composed of " << i << " capacitros computed, time elapsed " << (duration<double>(end-start)).count() << " sec" << endl;
	}

	cout << "Number of unique capacitance values is : " << capacitanceCircuits.ShowUniqueCap();
	cin.get();
	return 1;
}

