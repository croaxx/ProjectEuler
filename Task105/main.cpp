#include <stdio.h>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

using vecInts = vector<int>;
using setInts = set<int>;
using vecVecInts = vector<vecInts>;
using vecSets = vector<setInts>;
using vecPairSets = vector<pair<setInts, setInts>>;

auto MergeVectorsofSets( const vecSets& s1, const vecSets& s2 ) -> vecSets
{
	vecSets merged;

	for ( unsigned i = 0; i < s1.size(); ++i )
	{
		for ( unsigned j = 0; j < s2.size(); ++j )
		{
			setInts tmp( s1[i] );
			tmp.insert( begin(s2[j]), end(s2[j]) );

			if ( tmp.size() == s1[i].size() + s2[j].size() && find( begin(merged), end(merged), tmp ) == end(merged) )
				merged.push_back(move(tmp));
		}
	}

	return move(merged);
}

auto ConstructPairsOfEqualSets( const vecSets& s1, const vecSets& s2 ) -> vecPairSets
{
	vecPairSets pairs;

	for ( unsigned i = 0; i < s1.size(); ++i )
	{
		for ( unsigned j = 0; j < s2.size(); ++j )
		{
			setInts tmp( s1[i] );
			tmp.insert( begin(s2[j]), end(s2[j]) );

			if ( tmp.size() == s1[i].size() + s2[j].size() )
			{
				pairs.push_back( move(make_pair(s1[i], s2[j])) );
			}
		}
	}

	return move(pairs);
}

auto ConstructPairsOfUnequalSets( vecSets& s1, vecSets& s2 ) -> vecPairSets
{
	vecPairSets pairs;

	for ( unsigned i = 0; i < s1.size(); ++i )
	{
		for ( unsigned j = i + 1; j < s2.size(); ++j )
		{
			setInts tmp( s1[i] );
			tmp.insert( begin(s2[j]), end(s2[j]) );

			if ( tmp.size() == s1[i].size() + s2[j].size() )
			{
				pairs.push_back( move(make_pair(s1[i], s2[j])) );
			}
		}
	}

	return move( pairs );
}

auto GenMatrixDisjointSets( int min, int max) -> vector<vecPairSets>
{
	vector<vecPairSets> matrix;

	for ( int setLength = min; setLength <= max; ++setLength )
	{
		vector<vecSets> disjointSets;
		vecSets tmp;

		for ( int i = 0; i < setLength; ++i ) tmp.push_back( setInts {i});

		disjointSets.push_back( move(tmp) ) ;

		vecPairSets setPairs;

		for ( int i = 1; i < setLength - 1 ; ++i )
		{
			auto mergedSet = MergeVectorsofSets( disjointSets[0], disjointSets[i-1] );

			disjointSets.push_back( move(mergedSet) );
		}

		for ( int i = 1; i <= setLength/2 ; ++i )
		{
			for ( int j = i; j < setLength - i + 1; ++j )
			{
				vecPairSets newPairs;

				if ( i != j)
					newPairs = ConstructPairsOfEqualSets( disjointSets[i-1], disjointSets[j-1] );
				else
					newPairs = ConstructPairsOfUnequalSets( disjointSets[i-1], disjointSets[j-1] );

				setPairs.insert( end(setPairs), begin(newPairs), end(newPairs) );
			}
		}

		matrix.push_back( setPairs );
	}

	return move(matrix);
}

auto SumSubset( const vecInts& subset, setInts& sumIndices ) -> int
{
	int sum = 0;

	for ( const auto& e: sumIndices ) sum += subset[e];

	return sum;
}

auto CheckConditionsOnSubset( const vecInts& s, vecPairSets& disjointSubsets ) -> pair<bool, int>
{
	for ( unsigned i = 0; i < disjointSubsets.size(); ++i )
	{
		int sumB =  SumSubset( s, disjointSubsets[i].first );
		int sumC =  SumSubset( s, disjointSubsets[i].second );

		if ( sumB == sumC)
			return make_pair(false, 0);
		else if ( disjointSubsets[i].first.size() < disjointSubsets[i].second.size() && sumC < sumB )
			return make_pair(false, 0);
	}

	int setTotalSum = accumulate( begin(s), end(s), 0 );

	return make_pair(true, setTotalSum );
}

auto ReadSubsetVector( const string path ) -> vecVecInts
{
	vecVecInts sets;

	ifstream file(path);

	string line;

	while ( getline(file, line) )
	{
		stringstream ss(line);
	    int i;
	    vecInts tmp;

	    while (ss >> i)
	    {
	    	tmp.push_back(i);

	        if (ss.peek() == ',')
	            ss.ignore();
	    }
	    sets.push_back( tmp );
	}

	return move( sets );
}

auto main() -> int
{
	const string path = "/home/croax/Desktop/p105_sets.txt";
	int minSetLength = 7, maxSetLength = 12;
	int setsCounter = 0, sumSets = 0;

	vecVecInts inputSets = ReadSubsetVector( path );
	vector<vecPairSets> matrixDisjointSets = GenMatrixDisjointSets( minSetLength, maxSetLength );

	for ( unsigned i = 0; i < inputSets.size(); ++i )
	{
		auto res = CheckConditionsOnSubset( inputSets[i], matrixDisjointSets[inputSets[i].size() - minSetLength] );

		if ( res.first )
		{
			++setsCounter;
			sumSets += res.second;
		}
	}

	printf( "Number of special sets is: %d\n", setsCounter );
	printf( "The sum is: %d\n", sumSets );
}
