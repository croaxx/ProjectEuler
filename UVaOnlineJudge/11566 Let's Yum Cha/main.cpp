// Problem description: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2613
// Time complexity: O(K*x*N^2), space: O(K*x*N^2)

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

const int MIN = INT32_MIN / 2;
int N, x, T, K, max_money, people;

int maximize_favor(int idx, int spent, int items, const vi& prices, const vi& favors, vvvi& memo)
{
    int to_be_paid = ceil((spent + (N + 1) * T) * 1.1L); // L is important for precision
    if (items > 2*people || to_be_paid > max_money) return MIN;
    if (idx >= prices.size() || to_be_paid == max_money) return 0;

    int& ans = memo[idx][spent][items];
    if (ans != -1) return ans;

    // buy one dish
    int favor1 = favors[idx] + maximize_favor(idx + 1, spent + prices[idx], items + 1, prices, favors, memo);
    // buy two dishes
    int favor2 = 2*favors[idx] + maximize_favor(idx + 1, spent + 2*prices[idx], items + 2, prices, favors, memo);
    // don't buy this type
    int favor3 = maximize_favor(idx + 1, spent, items, prices, favors, memo);

    return ans = max(favor1, max(favor2, favor3));
}

int main()
{
    cin >> N >> x >> T >> K;
    while (N + x + T + K != 0 )
    {
        people = N + 1;
        max_money = x * people;
        vi prices(K), favors(K);
        for (int i = 0; i < K; ++i)
        {
            cin >> prices[i];
            int dimsum_favor_total = 0;
            for (int j = 0; j < people; ++j)
            {
                int favor; cin >> favor;
                dimsum_favor_total += favor;
            }
            favors[i] = dimsum_favor_total;
        }
        vvvi memo(K+1, vvi(x*(people+1), vi(2*(people+1), -1)));
        int favor = maximize_favor(0, 0, 0, prices, favors, memo);
        double mean_favor = double(favor) / (double)people;
        printf("%.2lf\n", mean_favor);
        cin >> N >> x >> T >> K;
    }
    return 0;
}
