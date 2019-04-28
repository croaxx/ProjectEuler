// Problem definition: https://leetcode.com/problems/recover-binary-search-tree/

// Time complexity: O(n) Morris inorder traversal 
// Space complexity: O(1) (due to threaded binary tree, which avoids stack allocation)

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
private:
    int INF = INT32_MAX;    
public:
    void assignSwapNodes(TreeNode* cur, TreeNode*& prev, TreeNode*& lhs, TreeNode*& rhs)
    {
        if (cur->val < prev->val)
        {
            if (lhs == nullptr) lhs = prev;
            rhs = cur;
        }
        prev = cur;
    }
    
    void recoverTree(TreeNode* root)
    {
        if (root == nullptr) return;
        TreeNode* current = root, *prev = new TreeNode(-INF), *pred, *lhs, *rhs;
        lhs = rhs = pred = nullptr;
        while (current != nullptr)
        {
            if (current->left == nullptr)
            {
                assignSwapNodes(current, prev, lhs, rhs);
                current = current->right;
            }
            else
            {
                pred = current->left;
                while (pred->right != nullptr && pred->right != current) pred = pred->right;
                if (pred->right == nullptr)
                { 
                    pred->right = current; 
                    current = current->left; 
                }
                else
                {
                    assignSwapNodes(current, prev, lhs, rhs);
                    pred->right = nullptr; 
                    current = current->right; 
                }
            }
        }
        swap(lhs->val, rhs->val);
    }
};


