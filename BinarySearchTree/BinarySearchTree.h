#include<iostream>
using namespace std;
template<class K>
 struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		:_left(nullptr)
		, _right(nullptr)
		,_key(key)
	{}
};

template<class K>
class BSTree
{
public:
	typedef BSTreeNode<K> Node;
	BSTree()
		:_root(nullptr)
	{}

	~BSTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}

	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root);
	}

	BSTree<K>& operator=(BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}


	//1.插入
	//非递归
	bool Insert(const K& key)
	{
		//_root为空，直接赋给_root
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		//从上往下遍历，key比cur的_key大就走右，小就走左
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			//相等就return false
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		//找到了合适的位置，判断是连左还是连右
		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}

	//递归
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	//2.中序遍历
	void InOrder()
	{
		//为了调用的时候不传参数
		_InOrder(_root);
		cout << endl;
	}

	//3.查找
	//非递归
	Node* Find(const K& key)
	{
		if (_root == nullptr)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
				cur = cur->_right;
			else if (key < cur->_key)
				cur = cur->_left;
			else
				return cur;
		}
		return NULL;
	}

	//递归
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	//4.删除
	//非递归
	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//找到了，准备删除
				//(1) cur的左边是空，将parent指向cur的右边
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						if (cur == parent->_right)
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
				}
				//(2) cur的右边是空，将parent指向cur的左边
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						if (cur == parent->_right)
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				//(3) cur的两边都不为空
				else
				{
					//找到左边最大的
					Node* leftmax_parent = cur;//这里不能是nullptr，如果leftmax->right为空，进不去循环leftmax_parent始终为nullptr,引发崩溃
					Node* leftmax = cur->_left;
					while (leftmax->_right != nullptr)
					{
						leftmax_parent = leftmax;
						leftmax = leftmax->_right;
					}
					//将找到的最大值leftmax替换cur,再删除leftmax
					cur->_key = leftmax->_key;
					
					//不可以if(leftmax->_left == nullptr)
					if (leftmax_parent->_right == leftmax)
					{
						leftmax_parent->_right = leftmax->_left;
					}
					else
					{
						leftmax_parent->_left = leftmax->_left;
					}
					delete leftmax;
				}
				return true;
			}
		}
		return false;
	}

	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

private:
	Node* _root;

	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* newnode = new Node(root->_key);
		newnode->_left = _Copy(root->_left);
		newnode->_right = _Copy(root->_right);
		return newnode;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << ' ';
		_InOrder(root->_right);
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->_key == key)
		{
			return root;
		}
		else if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return _FindR(root->_right, key);
		}
	}

	bool _InsertR(Node*& root, const K& key)
		//Node*& root 改变root的同时也改变了上级的root->_left或者root->_right
		//root 是root->_left或者root->_right的别名
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}

		if (root->_key < key)
		{
			return _InsertR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key);
		}
		else
		{
			return false;
		}
	}

	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_key > key)
		{
			return _EraseR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else
		{
			//删除
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;
			}
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;
			}
			else
			{
				Node* leftmax_parent = root;
				Node* leftmax = root->_left;
				while (leftmax->_right)
				{
					leftmax_parent = leftmax;
					leftmax = leftmax->_right;
				}
				root->_key = leftmax->_key;
				if (leftmax_parent->_right == leftmax)
				{
					leftmax_parent->_right = leftmax->_left;
				}
				else
				{
					leftmax_parent->_left = leftmax->_left;
				}
				delete leftmax;
			}
			return true;
		}
	}
};