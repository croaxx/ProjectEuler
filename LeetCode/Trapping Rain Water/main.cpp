// Problem description: https://leetcode.com/problems/trapping-rain-water/

// Solution: each i-th bar contributes with the following water amount: height[i] - min(h_left[i], h_right[i]) (if non negative)
// Here h_left[i]/h_right[i] indicates the maximum available height of the bar to the left/right from i-th bar.
// Thus, h_left[i]/h_right[i] are strictly non decreasing/increasing arrays.
// E.g. for the input: [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
// h_left = [-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3]
// h_right = [3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, -1]

// Time complexity: O(n)
// Space complexity: O(n) - two arrays

class Solution
{
private:
	using vi = vector<int>;
public:
	int trap(vi& height)
	{
		int N = height.size();
		if (N <= 2) return 0;
		vi h_left(N, -1), h_right(N, -1);
		int h_max_left = height.front(), h_max_right = height.back();
		for (int i = 1; i < N; ++i)
		{
			h_left[i] = max(h_left[i - 1], h_max_left);
			h_right[N-i-1] = max(h_right[N-i], h_max_right);
			h_max_left = max(h_max_left, height[i]);
			h_max_right = max(h_max_right, height[N-i-1]);
		}
		int s = 0;
		for (int i = 0; i < N; ++i)
		{
			int h_min = min(h_left[i], h_right[i]);
			if (height[i] < h_min) s += h_min - height[i];
		}
		return s;
	}
};
