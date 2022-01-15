/*
 * @Author: A-ZONE-LC
 * @Date: 2022-01-14 17:02:45
 * @LastEditTime: 2022-01-15 19:24:41
 * @LastEditors: Please set LastEditors
 * @Description: 测试程序
 * @FilePath: \data-struct-STL-simulation\HasHtable Simulate\test.cpp
 */


#include"unordered_set.h"
#include"unordered_map.h"

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


void test2()
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
int main()
{
    //test1();
    test2();
    return 0;
}