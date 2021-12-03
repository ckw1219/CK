/*
LRU算法(页面置换算法):把最近最少使用的数据从cache中剔除

1：只提供两个接口：1，获取数据 2，写入数据
2：无论是获取还是写入数据，当前数据要保持在最容易访问的位置
3：缓存数量有限，最长时间没被访问的数据应该置换出缓存

实现：利用双向链表
设置一个虚拟头节点和尾节点，每次访问完数据(不管写入还是读取)，都将该节点调整到头节点

利用模板去改写函数，并且提高查找效率
*/
#include<iostream>
#include<map>

using namespace std;

//利用模板可以使得key和val的值为多种不同类型
template< class K, class V >
struct _Node_
{
    K key;
    V value;
    //双向链表结构
    struct _Node_* next;
    struct _Node_* pre;
};
//typedef和template联合使用的时候，typedef必须定义在template的下方

template<class K, class V>
class LRUCache
{
    public:
        typedef _Node_<K, V> CacheNode;
        LRUCache(int cache_size = 10);//缓存固定大小
        ~LRUCache();
        V getValue(K key);
        map<K,CacheNode*> mp;
        bool putValue(K key, V value);
        void displayNodes();

    private:
        int cache_size_;
        int cache_used_size_;
        CacheNode* p_cache_head;
        CacheNode* p_cache_near;
        void detachNode(CacheNode* node);
        void addToFront(CacheNode* node);
};

template<class K, class V>
LRUCache<K,V>::LRUCache(int cache_size)
{
    cache_size_ = cache_size;
    cache_used_size_ = 0;
    p_cache_head = new CacheNode();
    p_cache_near = new CacheNode();
    
    p_cache_head->next = p_cache_near;
    p_cache_head->pre = NULL;

    p_cache_near->pre = p_cache_head;
    p_cache_near->next = NULL;
}

template<class K, class V>
LRUCache<K,V>::~LRUCache()
{
    CacheNode* p = p_cache_head;
    while (p->next != NULL)
    {
        delete p->pre;
        p = p->next;
    }
    delete p_cache_near;
}

template<class K, class V>
void LRUCache<K,V>::detachNode(CacheNode* node)
{
    node->pre->next = node->next;
    node->next->pre = node->pre;
}

template<class K, class V>
void LRUCache<K,V>::addToFront(CacheNode* node)
{
    node->next = p_cache_head->next;
    p_cache_head->next->pre = node;
    p_cache_head->next = node;
    node->pre = p_cache_head;
}

template<class K, class V>
V LRUCache<K,V>::getValue(K key)
{
    if (mp.count(key))
    {
        detachNode(mp[key]);
        addToFront(mp[key]);
        return mp[key]->value;
    }

    return -1;
}

template<class K, class V>
bool LRUCache<K,V>::putValue(K key, V val)
{
    //缓存是否命中
    CacheNode* p = p_cache_head->next;
    while (p->next != NULL)
    {
        if (p->key == key)
        {
            p->value = val;
            getValue(key);
            return true;
        }
        p = p->next;
    }

    if (cache_used_size_ >= cache_size_)
    {
        cout << "free" << endl;
        p = p_cache_near->pre->pre;
        delete p->next;
        p->next = p_cache_near;
        p_cache_near->pre = p;
    }

    p = new CacheNode();
    if (p == NULL) return false;
    addToFront(p);
    p->key = key;
    p->value = val;
    cache_size_++;
    return true;
}

template<class K, class V>
void LRUCache<K,V>::displayNodes()
{
    CacheNode* p = p_cache_head->next;
    while (p->next != NULL)
    {
        cout << "key :" << p->key << typeid(p->key).name();
        cout << " ";
        cout << "value :" << p->value << endl;
        p = p->next;
    }
}


int main()
{
    LRUCache<double,double>* LRU = new LRUCache<double, double>();
    LRU->displayNodes();
    LRU->putValue(9,10);
    LRU->getValue(8);

    LRU->putValue(7,11);
    LRU->putValue(6,12);

    LRU->displayNodes();
    return 0;
}