// Problem description: https://leetcode.com/problems/merge-k-sorted-lists/

// Time complexity: O(nlogk) - O(logk) get/extract min element from priority queue;
// n total sum of number of elements in all k lists
// Space complexity: O(n) - build new list

#include <queue>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct NodesComparer
{
    inline bool operator()(const ListNode* lhs, const ListNode* rhs) const
    {
        return lhs->val > rhs->val;
    }
};

class Solution
{
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		priority_queue<ListNode*, vector<ListNode*>, NodesComparer> pq;
		for (auto& e : lists)
		{
			if (e != nullptr)
			{
				pq.push(e);
				e = e->next;
			}
		}
		ListNode* current = nullptr;
		ListNode* root = nullptr;
		while (!pq.empty())
		{
			auto node = pq.top(); pq.pop();
			if (current == nullptr) // first node determines the root
			{
				current = new ListNode(node->val);
				root = current;
			}
			else
			{
				current->next = new ListNode(node->val);
				current = current->next;
			}
			node = node->next;
			if (node != nullptr) pq.push(node);
		}
		return root;
	}
};
