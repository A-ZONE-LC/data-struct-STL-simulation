/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-15 20:46:23
 * @LastEditTime: 2022-01-15 21:25:03
 * @LastEditors: Please set LastEditors
 * @Description: 用BitSet实现布隆过滤器
 * @FilePath: \data-struct-STL-simulation\HashTable\BloomFilter.h
 */

#pragma once
#include"bitset.h"


struct HashBKDR     //*BKDR哈希函数
{
    size_t operator()(const std::string& str)
    {
        size_t val = 0;
        for(auto ch: str)
        {
            val += ch;
            val *= 131;
        }
        return val;
    }
};

struct HashAP   //*AP哈希函数
{
    size_t operator()(const std::string& s)
    {
        register size_t hash = 0;
		size_t ch;
		for (long i = 0; i < s.size(); i++)
		{
			ch = s[i];
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
    }
};

struct HashDJB  //*DJB哈希函数
{
    size_t operator()(const std::string& s)
    {
        register size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
    }
};

namespace MyBitSet
{
    template<size_t N, class K = std::string, class HashFcn1 = HashBKDR, class HashFcn2 = HashAP, class HashFcn3 = HashDJB>
    class BloomFilter
    {
    public:
        void set(const K& key)  //*插入数据
        {
            size_t bit_pos1 = HashFcn1()(key) % N;
            size_t bit_pos2 = HashFcn2()(key) % N;
            size_t bit_pos3 = HashFcn3()(key) % N;

            _bitset.set(bit_pos1);
            _bitset.set(bit_pos2);
            _bitset.set(bit_pos3);
        }

        bool check(const K& key)    //!如果key不在bitset中，那必是准确的；但key在bitset中，可能存在误判
        {
            size_t bit_pos1 = HashFcn1()(key) % N;
            if(_bitset.check(bit_pos1) == false)
                return false;
            size_t bit_pos2 = HashFcn2()(key) % N;
            if(_bitset.check(bit_pos2) == false)
                return false;
            size_t bit_pos3 = HashFcn3()(key) % N;
            if(_bitset.check(bit_pos3) == false)
                return false;
            return true;
        }
    private:
        BitSet<N> _bitset;
    };
}
