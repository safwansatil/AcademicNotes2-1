#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void BFS(TreeNode *root)
{
    if (!root)
        return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        cout << current->val << " "; // Process node

        // Enqueue children (next level)
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}