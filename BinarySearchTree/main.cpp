#include"BinarySearchTree.h"
using namespace std;

int main()
{
	BSTree<int> tree;
	int a[] = { 6,1,7,3,8,5,0,9,11 };
	for (auto e : a)
	{
		tree.InsertR(e);
	}
	tree.InOrder();
	
	
	for (auto e : a)
	{
		tree.EraseR(e);
		tree.InOrder();
	}

	
	
	return 0;
}