// Project Euler Task 128
// It can be observed that pd(n)=3 may appear only on the vertical elements: 1, 2, 8, 20, 38, 62, 128,...
// or on the elements next to the vertical ones, i.e, 7, 19, 37, 61, 127, ...
// Thus, only these sets of elements should be tested for pd(n)=3 condition

#include <stdio.h>
#include <set>
#include <string.h>

using namespace std;

using setType = long long int;

// Set of prime numbers
set<setType> get_primes(setType max)
{
    set<setType> primes;
    char *sieve;
    sieve = new char[max/8+1];

    memset(sieve, 0xFF, (max/8+1) * sizeof(char));

    for(setType x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8)))
		{
			primes.insert(x);

			for(setType j = 2*x; j <= max; j += x)
				sieve[j/8] &= ~(0x01 << (j % 8));
		}

    delete[] sieve;

    return primes;
}

auto ComputePDVecrtical(setType n, const set<setType>& primes) -> int
{
	int primeCounter = 0;

	if (primes.find(6 * n - 1) != end(primes))
		++primeCounter;

	if (primes.find(6 * n + 1) != end(primes))
		++primeCounter;

	if (primes.find(12 * n + 5) != end(primes))
		++primeCounter;

	return primeCounter;
}

auto ComputePDOffVecrtical(setType n, const set<setType>& primes) -> int
{
	int primeCounter = 0;

	if (primes.find(12 * n - 7) != end(primes))
		++primeCounter;

	if (primes.find(6 * n - 1) != end(primes))
		++primeCounter;

	if (primes.find(6 * n + 5) != end(primes))
		++primeCounter;

	return primeCounter;
}

auto main() -> int
{
	setType N = 80000;
	auto primes = get_primes(100000000);

	int pdCounter = 2;

	for (setType i = 2; i < N; ++i)
	{
		setType number = 3*i*(i-1)+2;
		auto pd = ComputePDVecrtical(i, primes);

		if (pd == 3)
			printf("tile %lld is %lldth with pd %d\n", number, ++pdCounter, pd);

		pd = ComputePDOffVecrtical(i, primes);
		if (pd == 3)
			printf("tile %lld is %lld-th with pd %d\n", 3*i*(i+1)+1, ++pdCounter, pd);
	}

	printf("success!\n");
	return 1;
}

