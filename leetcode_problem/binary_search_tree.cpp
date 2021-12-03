#include<iostream>
#include<vector>
/*
抽象数据类型bsTree
bsTree{
     实例：每一个节点都有一个数对，其中一个成员是关键字，一个成员是数值；所有关键字都不相同
     任何一个节点的左子树的关键字小于该节点，右子树的关键字大于该节点
     操作：
        find(k):返回关键字为k的数对
        insert(p):插入数对p
        erase(k):删除关键字为k的数对
        ascend():按关键字升序输出所有数对                                                  
}
*/
struct treeNode
{
    int val;
    int k;
    treeNode(int _k, int _val):k(_k),val(_val) {
        this->left = nullptr;
        this->right = nullptr;
    }
    treeNode* left;
    treeNode* right;
};

