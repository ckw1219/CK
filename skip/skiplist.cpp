/* ************************************************************************
> File Name:     skiplist.h
> Author:        程序员Carl
> 微信公众号:    代码随想录
> Created Time:  Sun Dec  2 19:04:26 2018
> Description:   
 ************************************************************************/

#include<iostream>
#include<cmath>
#include<cstdlib>
#include<mutex>
#include<fstream>
#include<cstring>

#define STORE_FILE "store/dumpFile" //存储路径

std::mutex mtx;
std::string delimiter = ":";

//跳表节点
template<typename K, typename V>
class Node
{
    public:
        Node() {}
        Node(K k, V v, int);

        K get_key() const;
        V get_value() const;

        void set_value(V);

        //forward是一个指针，指向的空间存放的是Node<K,V>*类型的数据
        Node<K,V>* *forword;//指针指向下一层节点(节点是指针类型，所以是**) 
        ~Node();
        
        int node_level;
    private:
        K key;
        V value;
};

template<typename K, typename V>
Node<K,V>::Node(const K k, const V v, int level)
{
    this->key = k;
    this->value = v;
    this->node_level = level;

    this->forword = new Node<K, V>*[level+1];
    memset(this->forword, 0, sizeof(Node<K,V>*)*(level=1));
};

template<typename K, typename V>
Node<K, V>::~Node()
{
    delete []forword;
};

template<typename K, typename V>
K Node<K, V>::get_key() const
{
    return key;
};

template<typename K, typename V>
V Node<K, V>::get_value() const
{
    return value;
};

template<typename K, typename V>
void Node<K, V>::set_value(V value)
{
    this->value = value;
}


// Class template for Skip list 模板跳表
template <typename K, typename V>
class SkipList
{
    public:
        SkipList(int);
        ~SkipList();

        int get_random_level();

        Node<K, V>* create_node(K, V, int);

        int insert_element(K, V);
        void display_list();
        bool search_element(K);
        void delete_element(K);
        void dump_file();
        void load_file();
        int size();
    
    private:
        void get_key_value_from_string(const std::string& str, std::string* key, std::string* value);
        void is_valid_string(const std::string& str);

    private:
        int _max_level;

        int _skip_list_level;

        Node<K, V> *_header;

        std::ofstream _file_writer;
        std::ifstream _file_reader;

        int _element_count;
};







int main()
{

}
