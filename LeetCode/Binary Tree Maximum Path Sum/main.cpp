// Problem definition: https://leetcode.com/problems/binary-tree-maximum-path-sum/

// Time complexity: O(n) postorder traversal
// Space complexity: O(n) function call-stack allocation

// Note: space complexity can be made O(1) by using Morris traversal of threaded tree

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
    int INF = INT32_MAX;
    int max_sum = -INF;
public:
    int maxPathAtNode(TreeNode* node)
    {
        if (node == nullptr) return -INF;
        int L = max(0, maxPathAtNode(node->left));
        int R = max(0, maxPathAtNode(node->right));
        int path_sum = node->val + L + R;
        max_sum = max(max_sum, path_sum);
        return max(L, R) + node->val;
    }
    
    int maxPathSum(TreeNode* root)
    {
        maxPathAtNode(root);
        return max_sum;
    }
};
