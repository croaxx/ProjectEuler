// Problem definition: https://www.hackerrank.com/challenges/summing-pieces/problem
// Time complexity: O(n); Space complexity O(n), O(1) is possible

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

using lli = long long int;
using vi = vector<lli>;

lli modpow(lli base, lli exp, lli modulus)
{
    base %= modulus;
    lli result = 1;
    while (exp > 0)
    {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main()
{
    lli N = 1000000007, sum = 0, len, middle;
    lli n; cin >> n;

    if (n % 2 == 0) len = n / 2;
    else len = n / 2 + 1;
    middle = len - 1;

    vi A(n), B(len);

    for (lli i = 0; i < n; ++i) cin >> A[i];

    B[0] = modpow(2, n, N) - 1;
    for (lli i = 1; i < len; ++i)
        B[i] = (B[i-1] % N + modpow(2, n - 1 - i, N) - modpow(2, i - 1, N)) % N;

    for (lli i = 0; i < n; ++i)
    {
        lli idx = i;
        if (i >= middle + 1) idx = n - i - 1;
        sum = (sum % N + (A[i] % N) * (B[idx] % N) % N);
    }

    printf("%lld", sum % N);
    return 0;
}
