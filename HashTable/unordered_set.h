/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-15 16:18:48
 * @LastEditTime: 2022-01-15 17:34:18
 * @LastEditors: Please set LastEditors
 * @Description: 使用开散列哈希实现hash_set
 * @FilePath: \data-struct-STL-simulation\HashTable\unordered_set.h
 */

#pragma once
#include"hashtable.h"

namespace MyHash
{
    template<class K>
    class unordered_set
    {
    public:
        struct KeyOfSet     //*仿函数取键值
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };

        typedef typename HashTable<K, K, KeyOfSet>::iterator iterator; //!使用typename声明iterator是类型

        iterator begin()
        {
            return _hash.begin();
        }

        iterator end()
        {
            return _hash.end();
        }

        pair<iterator, bool> insert(const K& key)
        {
            return _hash.insert(key);
        }

        bool erase(const K& key)
        {
            return _hash.erase(key);
        }

        bool contain(const K& key)
        {
            iterator find_ret = _hash.find(key);
            if(find_ret != end())
                return true;
            else
                return false;
        }
    private:
        HashTable<K, K, KeyOfSet> _hash; //*hash_set的底层结构
    };
}
