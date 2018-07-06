// Problem definition: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2451

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;
typedef vector<int> vi;

int main()
{
    int tests; cin >> tests;
    for(int t = 0; t < tests; ++t)
    {
        int n; cin >> n;
        if (n == 0)
        {
            printf("0\n");
            continue;
        }
        vi arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];  
	reverse(begin(arr), end(arr));
        vi lis(n, 1), lds(n, 1), lms(n, 1);
        int longest = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                    lis[i] = lis[j] + 1;

                if (arr[i] < arr[j] && lds[i] < lds[j] + 1)
                    lds[i] = lds[j] + 1;
            }
            longest = std::max(longest, lis[i] + lds[i] - 1);
        }
        printf("%d\n", longest);
    }
    return 0;
}
