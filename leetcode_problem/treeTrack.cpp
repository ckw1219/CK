/*
二叉树的递归写法有无返回值的区别。

从路径查找的逻辑去判断
1：有返回值
    代表查找到某条路径之后，立即返回，不需要搜索整颗树
2：无返回值
    需要搜索整颗树
*/

#include<iostream>

using namespace std;


typedef struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int val_) : val(val_) {}
} TreeNode;

class solusion
{
    public:
        bool flag = false;
        void dfs(TreeNode* root, int val)
        {
            if (root == nullptr) return;
            if (!root->left && !root->right && val == 0)
            {
                flag = true;
                return;
            }
            dfs(root->left, val-root->val);
            dfs(root->right, val-root->val);
        }

        bool flag1 = false;
        void dfs1(TreeNode* root, int val)
        {
            if (flag1) return;//找到之后立即返回
            if (root == nullptr) return;
            if (!root->left && !root->right && val == 0)
            {
                flag1 = true;
                return;
            }
            dfs1(root->left, val-root->val);
            dfs1(root->right, val-root->val);
        }

        bool dfs2(TreeNode* root, int val)
        {
            if (root == nullptr) return false;
            if (!root->left && !root->right && val == 0) return true;
            if (dfs2(root->left, val-root->val)) return true;
            if (dfs2(root->right, val-root->val)) return true;
        }
};

int main 
{
    return 0;
}