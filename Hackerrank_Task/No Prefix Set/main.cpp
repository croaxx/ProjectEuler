// Problem : https://www.hackerrank.com/challenges/no-prefix-set/problem

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <memory>

using namespace std;

class Dictionary
{
private:
    struct Node
    {
        bool isEnd;
        unordered_map<char, shared_ptr<Node>> nodes;
        Node(bool is_end): isEnd{is_end}{}
    };
    shared_ptr<Node> root;
public:
    Dictionary()
    {
        root = make_shared<Node>(false);
    }
    bool add(const string& s)
    {
        auto ptr = root;
        for (int i = 0; i < s.size(); ++i)
        {
            auto it = ptr->nodes.find(s[i]);
            if (it == end(ptr->nodes))
            {
                bool isEnd = false;
                if (i == s.size() - 1) isEnd = true;
                auto p = make_shared<Node>(isEnd);
                ptr->nodes.insert(make_pair(s[i], p));
                ptr = p;
            }
            else
            {
                if (it->second->isEnd) return false;
                else if (i == s.size() - 1) return false;
                ptr = it->second;
            }
        }
        return true;
    }
};

int main()
{
    int n; cin >> n;
    Dictionary t;
    for (int i = 0; i < n; ++i)
    {
        string word;
        cin >> word;
        if (!t.add(word))
        {
            printf("BAD SET\n");
            printf("%s", word.c_str());
            return -1;
        }
    }
    printf("GOOD SET\n");
    return 1;
}
