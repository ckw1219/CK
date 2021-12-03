#include"tree.h"
#include<vector>
#include<stack>
#include<algorithm>
/*
递归三部曲：
1：确定递归函数的参数和返回值
    确定哪些参数是递归的过程中需要处理的，那么就在递归函数里加上这个参数，
    并且要明确每次递归的返回值是什么进而确定递归函数的返回类型。
2：确定终止条件
    保证递归的运行有一个节点，不会无限递归，导致栈终止。
3：确定单层递归逻辑
    确定每一层递归需要处理的信息。在这里就需要重复调用自己来实现递归过程。

三种遍历加层次遍历
*/
class Solution
{
    public:
        void rec(TreeNode* root, vector<int>& res)//递归版本
        {
            if (root == nullptr) return;
            res.push_back(root->val);
            rec(root->left, res);
            rec(root->right, res);
        }

        // vector<int> preorder(TreeNode* root) //递归版本
        // {
        //     vector<int> res;
        //     rec(root, res);
        //     return res;
        // }


        vector<int> preorder(TreeNode* root) //迭代版本 前序遍历
        {
            stack<TreeNode*> stk;
            vector<int> res;
            if (root == nullptr) return res;
            stk.push(root);

            while (!stk.empty())
            {
                TreeNode* node = stk.pop();
                stk.pop();
                res.push_back(node->val);
                if (node->right) stk.push(node->right);
                if (node->left) stk.push(node->left);
            }

            return res;
        }

        vector<int> inorder(TreeNode* root)  //迭代版本，中序遍历
        {
            //难点：当前指针遍历的节点，并非是当前所需要处理的节点，
            //所有要先压入stack。
            vector<int> res;
            stack<TreeNode*> stk;
            if (root == nullptr) return res;
            stk.push(root);
            TreeNode* cur = root;
            //cur指向当前二叉树中的节点，当cur非空的时候，将节点压入栈中，当cur为空的时候,则开始处理节点，栈顶的元素，就是需要处理的节点。
            //处理完之后，将cur指针指向栈顶元素的右边节点，开始处理右子树。
            while ( cur != nullptr || !stk.empty()) //当根节点弹出的时候，此时，cur指向根节点的右边节点，stk为空，所有当cur不为空的时候，需要继续处理
            {
                if (cur != nullptr)
                {
                    stk.push(cur);
                    cur = cur->left;
                }
                else 
                {
                    TreeNode* node = stk.top();
                    stk.pop();
                    res.push_back(node->val);
                    cur = cur->right;
                }
            }

            return res;
        }

        vector<int> postorder(TreeNode* root) // 迭代版本，后序遍历
        {
            //后序遍历的顺序：左节点，右节点，根节点
            //先序遍历的顺序：根节点，左节点，右节点
            //将先序遍历的顺序调整一下：根节点，右节点，左节点。 然后再将res数组翻转即可。
            vector<int> res;
            stack<int> stk;
            if (root == nullptr) return res;
            stk.push_back(root);

            while (!stk.empty())
            {
                TreeNode* node = stk.top();
                stk.pop();
                res.push_back(node->val);
                if (node->right) stk.push(node->right);
                if (node->left) stk.push(node->left);
            }

            reverse(res.begin(), res.end());
            return res;
        }

        vector<int> levelorder(TreeNode* root)
        {
            vector<int> res;
            if (root == nullptr) return res;
            deque<int> stk;
            stk.push(root);
            int count = stk.size();
            while (!stk.empty())
            {
                for (int i = 0; i < count; i++)
                {
                    TreeNode* node = stk.top();
                    stk.pop();
                    res.push_back(node->val);
                    if (node->left) stk.push(node->left);
                    if (node->right) stk.push(node->right);
                }
                count = stk.size();
            }

            return res;
        }
};


int main()
{
    Solution s;
    TreeNode* root = new TreeNode(1);
    
    vector<int> res = s.preorder(root);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }

    system("pause");
    return 0;
}