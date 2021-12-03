//代码随想录，二叉树专题
#include<iostream>

using namespace std;


struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x): val(x), left(NULL), right(NULL) {}

    TreeNode():val(0), left(NULL), right(NULL) {}
};