/*
LRU算法(页面置换算法):把最近最少使用的数据从cache中剔除

1：只提供两个接口：1，获取数据 2，写入数据
2：无论是获取还是写入数据，当前数据要保持在最容易访问的位置
3：缓存数量有限，最长时间没被访问的数据应该置换出缓存

实现：利用双向链表
设置一个虚拟头节点和尾节点，每次访问完数据(不管写入还是读取)，都将该节点调整到头节点

*/

#include<iostream>

using namespace std;

//双向链表节点
typedef struct _Node_ {
    int key = -1;
    int val = -1;
    struct _Node_ *next;
    struct _Node_ *pre;
}CacheNode;

class LRUCache
{
    public:
            LRUCache(int cache_size = 10);
            ~LRUCache();
            int getValue(int key);
            bool putValue(int key, int val);
            void displayNodes();
    private:
            int cache_size_;
            int cache_real_size_;
            CacheNode *p_cache_list_head;
            CacheNode *p_cache_list_near;
            void detachNode(CacheNode* node);
            void addToFront(CacheNode* node);
};

LRUCache::LRUCache(int cache_size)
{
    cache_size_ = cache_size;
    cache_real_size_ = 0;
    p_cache_list_head = new CacheNode();
    p_cache_list_near = new CacheNode();
    p_cache_list_head->next = p_cache_list_near;
    p_cache_list_head->pre = NULL;
    p_cache_list_near->next = NULL;
    p_cache_list_near->pre = p_cache_list_head;
}

LRUCache::~LRUCache()
{
    CacheNode *p = p_cache_list_head->next;
    while (p->next != NULL)
    {
        delete p->pre;
        p = p->next;
    }
    delete p_cache_list_near;
}

void LRUCache::detachNode(CacheNode* node)
{
    node->pre->next = node->next;
    node->next->pre = node->pre;
}

void LRUCache::addToFront(CacheNode* node)
{
    //写法1
    CacheNode* temp_next = p_cache_list_head->next;
    p_cache_list_head->next = node;
    node->next = temp_next;
    temp_next->pre = node;
    node->pre = p_cache_list_head;

    //写法2
    // node->next = p_cache_list_head->next;
    // p_cache_list_head->next->pre = node;
    // p_cache_list_head->next = node;
    // node->pre = p_cache_list_head;

}
int LRUCache::getValue(int key)
{
    CacheNode* p = p_cache_list_head->next;

    while (p != nullptr)
    {
        if (p->key = key)
        {
            detachNode(p);
            addToFront(p);
            return p->val;
        }
        p = p->next;
    }
    return -1;
}

bool LRUCache::putValue(int key, int val)
{
    CacheNode* p =p_cache_list_head->next;
    while (p->next != nullptr)
    {
        if (p->key == key)
        {
            p->val = val;
            getValue(key);
            return true;
        }
        p = p->next;
    }

    if (cache_real_size_ >= cache_size_)
    {
        cout << "free" << endl;
        p = p_cache_list_near->pre->pre;
        delete p->next;
        p->next = p_cache_list_near;
        p_cache_list_near->pre = p;
    }
    p = new CacheNode();
    if (p == NULL) return false;
    addToFront(p);
    p->key = key;
    p->val = val;
    cache_size_++;
    return true;
}
void LRUCache::displayNodes()
{
    CacheNode* cur = p_cache_list_head->next;
    while (cur->next != nullptr)
    {
        cout << "key : " << cur->key << " " << "val : " << cur->val << endl;
        cur = cur->next;
    }
}

int main()
{
    LRUCache* LRU = new LRUCache();
    LRU->displayNodes();
    LRU->putValue(1,10);
    LRU->getValue(1);

    LRU->putValue(2,11);
    LRU->putValue(3,12);

    LRU->displayNodes();
    return 0;
}