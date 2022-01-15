/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-14 17:02:39
 * @LastEditTime: 2022-01-15 17:11:39
 * @LastEditors: Please set LastEditors
 * @Description: 开散列哈希表的实现
 * @FilePath: \data-struct-STL-simulation\HasHtable Simulate\hashtable.cpp
 */

#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace MyHash
{
    //*获得存储标识位的仿函数
    template<class K>
    struct HashFunc
    {
        size_t operator()(const K& key)
        {
            return key;
        }
    };


    //*对上面的仿函数的特化
    template<>
    struct HashFunc<string>
    {
        size_t operator()(const string& str)
        {
            size_t key = 0;
            for(auto e:str)
            {
                key += e;
                key *= 131;
            }
            return key;
        }
    };


    //*-----------------------------------------------------------------------------------------------------
    //*哈希结点
    template<class T>
    struct HashNode
    {
        HashNode<T>* _next;
        T _data;

        HashNode(const T& data) //!const T&
            :_data(data)
            ,_next(nullptr)
        {}
    };


    //*-----------------------------------------------------------------------------------------------------
    //*哈希表迭代器
    template<class K, class T, class KeyOfT, class HashFunc>
    class HashTable;
    template<class K, class T, class KeyOfT, class HashFunc = HashFunc<K>>
    struct HashTableIterator
    {
        typedef HashNode<T> Node;
        typedef HashTableIterator<K, T, KeyOfT, HashFunc> self;
        typedef HashTable<K, T, KeyOfT, HashFunc> HashTable;

        Node* _node;    //?哈希结点用于迭代器的迭代
        HashTable* _pht;     //?哈希表的指针用于链式结构走到结尾之后寻找下一个哈希桶

        HashTableIterator(Node* node, HashTable* pht) 
            :_node(node)
            ,_pht(pht)
        {}

        T& operator*()
        {
            return _node->_data;
        }

        T* operator->()
        {
            return &_node->_data;
        }

        bool operator==(const self& other)
        {
            return _node == other._node;
        }

        bool operator!=(const self& other)
        {
            return _node != other._node;
        }

        self& operator++()
        {
            if(_node->_next)    //?如果哈希桶没有遍历完，继续指向下一个节点
            {
                _node = _node->_next;
                return *this;
            }

            //?如果一个哈希桶遍历完了，就计算出目前哈希桶的位置，找到下一个哈希桶的位置
            size_t index = HashFunc()(KeyOfT()(_node->_data)) % (_pht->_table).size();
            ++index;
            while(index < _pht->_table.size())
            {
                if(_pht->_table[index])
                {
                    _node = _pht->_table[index];
                    return *this;
                }
                else
                    ++index;
            }
            _node = nullptr;    //?如果遍历完了都没有找到下一个节点，则下一个节点就是空，遍历结束
            return *this;
            
        }
    };


    //*-----------------------------------------------------------------------------------------------------
    //*哈希表
    template<class K, class T, class KeyOfT, class HashFunc = HashFunc<K>>
    class HashTable
    {
    public:
        typedef HashNode<T> Node;
        typedef HashTableIterator<K, T, KeyOfT, HashFunc> iterator;
        friend struct HashTableIterator<K, T, KeyOfT, HashFunc>;  //?声明友元类，因为在迭代器里会用到HashTable的私有成员_table

        HashTable()  //!这里使用 =default时n是随机值
            :_n(0)
        {}

        HashTable(const HashTable<K, T, KeyOfT, HashFunc>& t)   //todo(拷贝构造函数)
        {
            _n = t._n;
            _table.resize(t._table.size());
            for(int i=0; i<t._table.size(); i++)
            {
                if(t._table[i])
                {
                    Node* cur = t._table[i];
                    while(cur)
                    {
                        Node* newnode = new Node(cur->_data);   //?头插新构造的结点
                        newnode->_next = _table[i];
                        _table[i] = newnode;
                        cur = cur->_next;
                    }
                }
            }
        }

        HashTable<K, T, KeyOfT, HashFunc>& operator=(HashTable<K, T, KeyOfT, HashFunc> t)   //todo(赋值重载)
        {
            swap(_n, t._n);
            _table.swap(t._table);
            return *this;
        }

        ~HashTable()    //todo(析构函数)
        {
            for(int i=0; i<_table.size(); i++)
            {
                if(_table[i])
                {
                    Node* cur = _table[i];
                    while(cur)
                    {
                        _table[i] = cur->_next;
                        delete cur;
                        cur = _table[i];
                    }
                }
                _table[i] = nullptr;
            }
        }

        iterator begin()
        {
            size_t index = 0;
            while(index < _table.size())
            {
                if(_table[index] != nullptr)
                    return iterator(_table[index], this);
                else
                    ++index;
            }
            return iterator(nullptr, this);
        }


        iterator end()
        {
            return iterator(nullptr, this);
        }


        pair<iterator, bool> insert(const T& data) //todo(向哈希表中插入一个值)
        {
            KeyOfT getkey; //?仿函数对象，得到数据的键值
            HashFunc getlogo; //?仿函数对象，通过键值得到存储标志位

        /* 哈希插入的逻辑 
        1.查看插入的节点是否已经在哈希表中，如果在则插入失败
        2.如果哈希表的负载因子等于1则需要增容，增容需要重新开空间重新映射
        3.插入data构造的结点 */
            iterator find_ret = find(getkey(data));
            if(find_ret != end())
                return make_pair(find_ret, false);
            
            if(_n == _table.size())  //?负载因子等于1需要增容
            {
                vector<Node*> newtable;
                size_t newsize = _table.size() == 0 ? 8 : _table.size()*2; //?这里表的长度用素数更好，可以有效减少冲突
                newtable.resize(newsize, nullptr);
                for(int i=0; i<_table.size(); i++)  //?重新映射
                {
                    if(_table[i] != nullptr)
                    {
                        Node* cur = _table[i];
                        while(cur)
                        {
                            size_t newindex = getlogo(getkey(data)) % newtable.size();
                            Node* next = cur->_next;
                            cur->_next = newtable[newindex];   //?这里使用头插
                            newtable[newindex] = cur;
                            cur = next;
                        }
                        _table[i] = nullptr;    //?一个哈希桶处理完，将原来的哈希桶置空
                    }
                }
                _table.swap(newtable);  //?重新映射完毕，交换新的哈希表与旧的哈希表，哈希表增容完成
            }

            size_t index = getlogo(getkey(data)) % _table.size();
            Node* newnode = new Node(data);
            newnode->_next = _table[index];    //?头插
            _table[index] = newnode;
            ++_n;   //!注意有效值增加
            return make_pair(iterator(newnode, this), true);
        }


        //*通过键值查找删除
        bool erase(const K& key)
        {
            if(_table.size() == 0)
                return false;

            size_t index = HashFunc()(key) % _table.size();
            Node* cur = _table[index];
            Node* prev = nullptr;
            while(cur)
            {
                if(key == KeyOfT()(cur->_data))     //?找到要删除的位置
                {
                    if(cur == _table[index])        //?结点时链表的头结点和中间结点分情况处理
                        _table[index] = cur->_next;
                    else
                        prev->_next = cur->_next;
                    delete cur;
                    --_n;
                    return true;
                }
                else
                {
                    prev = cur;
                    cur = cur->_next;
                }
            }
            return false;
        }


        //*在哈希表中通过键值查找
        iterator find(const K& key)
        {
            if(_table.size() == 0)
                return iterator(nullptr, this);
            KeyOfT getkey; //?仿函数对象，得到数据的键值
            HashFunc getlogo;   //?仿函数对象，通过键值得到存储标志位
            size_t index = getlogo(key) % _table.size();
            Node* cur = _table[index];
            while(cur)
            {
                if(key == getkey(cur->_data)) //!为简单起见，这里==未使用仿函数替代,实际上要写出不同的特化的仿函数去比较各种类型的键值的大小，例如string,其他的自定义结构等
                    return iterator(cur, this);
                else
                    cur = cur->_next;
            }
            return iterator(nullptr, this);
        }
    private:
        vector<Node*> _table;
        size_t _n;
    };
}
