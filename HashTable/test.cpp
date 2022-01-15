/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-14 17:02:45
 * @LastEditTime: 2022-01-15 22:23:05
 * @LastEditors: Please set LastEditors
 * @Description: 测试程序
 * @FilePath: \data-struct-STL-simulation\HasHtable Simulate\test.cpp
 */


#include"unordered_set.h"
#include"unordered_map.h"
#include"bitset.h"
#include"BloomFilter.h"

void test1()    //todo(测试unordered_set接口)
{
    MyHash::unordered_set<int> uset;
    uset.insert(1);
    cout << "insert1" << endl;
    uset.insert(37);
    cout << "insert37" <<endl;
    uset.insert(99);
    cout << "insert99" <<endl;
    uset.insert(32);
    cout << "insert32" <<endl;
    uset.insert(5);
    cout << "insert5" <<endl;
    uset.insert(6);
    cout << "insert6" <<endl;

    cout << "contain 1?" << uset.contain(1) << endl;
    cout << "contain 0?" << uset.contain(0) << endl;

    cout << "erase 1?" << uset.erase(1) <<endl;
    cout << "erase 0?" << uset.erase(0) <<endl;
}


void test2()    //todo(测试unordered_map接口)
{
    MyHash::unordered_map<string, int> umap;
    umap.insert(make_pair("China", 1));
    cout << "insert china" << endl;
    umap.insert(make_pair("Chicken", 33));
    cout << "insert chicken" << endl;

    umap["iloveyou"] = 666;
    cout << "complete" << endl;

    cout << "contain iloveyou?" << umap.contain("iloveyou") << endl;
    cout << "contain ilove?" << umap.contain("ilove") << endl;

    umap.erase("iloveyou");
    cout << "contain iloveyou?" << umap.contain("iloveyou") << endl;

}

void test3()    //todo(测试bitset接口)
{
    MyBitSet::BitSet<24> bs;
    bs.set(10);
    bs.set(22);
    bs.set(21);
    bs.set(3);

    cout << "10 exist?" << bs.check(10) << endl;
    cout << "22 exist?" << bs.check(22) << endl;
    cout << "21 exist?" << bs.check(21) << endl;
    cout << "3 exist?" << bs.check(3) << endl;

    cout << endl;
    bs.unset(10);
    bs.unset(3);

    cout << "10 exist?" << bs.check(10) << endl;
    cout << "22 exist?" << bs.check(22) << endl;
    cout << "21 exist?" << bs.check(21) << endl;
    cout << "3 exist?" << bs.check(3) << endl;
}

void test_BloomFilter400()  //todo(测试布隆过滤器N = 400 时的误判率)
{
    MyBitSet::BloomFilter<400> bf;

	size_t N = 100;
	std::vector<std::string> v1;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://gitee.com/-/ide/project/bithange/class_code/ed";
		url += std::to_string(1234 + i);
		v1.push_back(url);
	}
	for (auto& str : v1)
	{
		bf.set(str);
	}
    size_t n = 0;
	/* for (auto& str : v1)
	{
        ++n;
		cout << n << ":" << bf.check(str) << endl;
	}
	cout << endl << endl; */
    std::vector<std::string> v2;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://www.cnblogs.com/-clqkfjgfngirtnhlkg05/31/2528153.html";
		url += std::to_string(13173 + i);
		v2.push_back(url);
	}
    size_t m = 0; 
    for(auto& str: v2)
    {
         if(bf.check(str))
            ++m;
    }
    cout << "bf400误判率:" << (double)m/(double)N << endl;
}

void test_BloomFilter600()  //todo(测试布隆过滤器N = 600 时的误判率)
{
    MyBitSet::BloomFilter<600> bf;

	size_t N = 100;
	std::vector<std::string> v1;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://gitee.com/-/ide/project/bithange/class_code/ed";
		url += std::to_string(1234 + i);
		v1.push_back(url);
	}
	for (auto& str : v1)
	{
		bf.set(str);
	}
    size_t n = 0;
	/* for (auto& str : v1)
	{
        ++n;
		cout << n << ":" << bf.check(str) << endl;
	}
	cout << endl << endl; */
    std::vector<std::string> v2;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://www.cnblogs.com/-clqkfjgfngirtnhlkg05/31/2528153.html";
		url += std::to_string(13173 + i);
		v2.push_back(url);
	}
    size_t m = 0; 
    for(auto& str: v2)
    {
         if(bf.check(str))
            ++m;
    }
    cout << "bf600误判率:" << (double)m/(double)N << endl;
}

void test_BloomFilter1000()  //todo(测试布隆过滤器N = 1000 时的误判率)
{
    MyBitSet::BloomFilter<1000> bf;

	size_t N = 100;
	std::vector<std::string> v1;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://gitee.com/-/ide/project/bithange/class_code/ed";
		url += std::to_string(1234 + i);
		v1.push_back(url);
	}
	for (auto& str : v1)
	{
		bf.set(str);
	}
    size_t n = 0;
	/* for (auto& str : v1)
	{
        ++n;
		cout << n << ":" << bf.check(str) << endl;
	}
	cout << endl << endl; */
    std::vector<std::string> v2;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://www.cnblogs.com/-clqkfjgfngirtnhlkg05/31/2528153.html";
		url += std::to_string(13173 + i);
		v2.push_back(url);
	}
    size_t m = 0; 
    for(auto& str: v2)
    {
         if(bf.check(str))
            ++m;
    }
    cout << "bf1000误判率:" << (double)m/(double)N << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    test_BloomFilter400(); //*误判率0.13
    test_BloomFilter600(); //*误判率0.03
    test_BloomFilter1000(); //*误判率0.00
    return 0;
}