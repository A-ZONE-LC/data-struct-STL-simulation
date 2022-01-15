/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-15 20:18:19
 * @LastEditTime: 2022-01-15 20:18:20
 * @LastEditors: Please set LastEditors
 * @Description: BitSet的模拟实现
 * @FilePath: \data-struct-STL-simulation\HashTable\bitset.h
 */
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<assert.h>

namespace MyBitSet
{
    template<size_t N>
    class BitSet
    {
    public:
        BitSet()
        {
            _bit.resize(N/32 +1);
        }

        void set(size_t x)  //*增加数据
        {
            assert(x < N);
            size_t i = x/32;
            size_t j = x%32;
            _bit[i] |= (1 << j);
        }

        void unset(size_t x)    //*删除数据
        {
            assert(x < N);
            size_t i = x/32;
            size_t j = x%32;
            _bit[i] &= (~(1 << j));
        }

        bool check(size_t x)    //*检查数据
        {
            assert(x < N);
            size_t i = x/32;
            size_t j = x%32;
            return _bit[i] & (1 << j);
        }
    private:
        vector<int> _bit;
    };
}