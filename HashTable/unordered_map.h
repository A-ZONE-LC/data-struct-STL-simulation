/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-15 18:16:49
 * @LastEditTime: 2022-01-15 18:16:49
 * @LastEditors: Please set LastEditors
 * @Description: 开散列哈希实现hash_map
 * @FilePath: \data-struct-STL-simulation\BinarySearchTree\unordered_map.h
 */

#pragma once
#include"hashtable.h"

namespace MyHash
{
    template<class K, class V>
    class unordered_map
    {
    public:
        struct KeyOfMap     //*仿函数取键值
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };

        typedef typename HashTable<K, pair<K, V>, KeyOfMap>::iterator iterator;  //!使用typename声明iterator是类型
        iterator begin()
        {
            return _hash.begin();
        }
        iterator end()
        {
            return _hash.end();
        }

        pair<iterator, bool> insert(const pair<K, V>& kv)  //*插入键值对
        {
            return _hash.insert(kv);
        }

        V& operator[](const K& key)     //*重载[]，使得可以直接修改key下的value
        {
            pair<iterator, bool> ret = _hash.insert(make_pair(key, V()));
            return ret.first->second;
        }

        bool erase(const K& key)
        {
            return _hash.erase(key);
        }

        iterator find(const K& key)
        {
            return _hash.find(key);
        }

        bool contain(const K& key)
        {
            iterator find_ret = find(key);
            if(find_ret != end())
                return true;
            else
                return false;
        }
    private:
        HashTable<K, pair<K, V>, KeyOfMap> _hash;   //*hash_map的底层结构
    };
}