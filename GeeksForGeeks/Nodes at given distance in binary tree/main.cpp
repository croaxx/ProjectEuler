// Problem definition: https://practice.geeksforgeeks.org/problems/nodes-at-given-distance-in-binary-tree/1

// Given a binary tree, a target node in the binary tree, and an integer value k,
// print all the nodes that are at distance k from the given target node. No parent pointers are available.
// Input: The first line of input contains an integer T denoting the number of test cases.
// Then T test cases follow. Each test case contains an integer n denoting the number of edges.
// Then the following line contains the edges as given in the example. The next line contains the target node.
// The last line of input contains the the value of distance k.
// Output: Print all the space separated nodes that are at distance k from the given target node.

// 1) Traverse part of the tree below the target node and print k distant nodes, while traversing
// 2) Disconnect the tree below the target node (target->left = target->right = nullptr)
// 3) Set target as new root, i.e., traverse the tree from the root till the target node and reverse the
// child/parent links on the way back (see function change_root)
// 4) Traverse the tree from the target node once again and print the rest of k distant nodes, while traversing

// Time complexity: O(n)

void printkdistanceNode(node *root, int k, int dist)
{
    if (root == nullptr) return;
    if (dist == k)
    {
        printf("%d ", root->data);
        return;
    }
    printkdistanceNode(root->left, k, dist + 1);
    printkdistanceNode(root->right, k, dist + 1);
}

bool change_root(node *cur, node *prev, node *target)
{
    if (cur == nullptr)
    {
        return false;
    }
    else if (cur == target || change_root(cur->left, cur, target))
    {
        cur->left = prev;
        return true;
    }
    else if (change_root(cur->right, cur, target))
    {
        cur->right = prev;
        return true;
    }
    return false;
}

int printkdistanceNode(node* root, node* target, int k)
{
    printkdistanceNode(target, k, 0); // traverse lower part of the tree
    target->left = target->right = nullptr; // disconnect the tree below the target node
    change_root(root, nullptr, target); // set target to be the root of the tree
    printkdistanceNode(target, k, 0); // traverse the upper part of the tree
}
