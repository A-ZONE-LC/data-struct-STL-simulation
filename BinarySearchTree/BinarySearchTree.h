#include<iostream>
using namespace std;
template<class K>
 struct BSTreeNode	//?树的节点
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
class BSTree	//?树的类
{
public:
	typedef BSTreeNode<K> Node;
	BSTree()	//todo(构造函数)
		:_root(nullptr)
	{}

	~BSTree()	//todo(析构函数)
	{
		_Destroy(_root);
		_root = nullptr;
	}

	BSTree(const BSTree<K>& t)	//todo(拷贝构造)
	{
		_root = _Copy(t._root);
	}

	BSTree<K>& operator=(BSTree<K> t)	//todo(赋值重载)
	{
		swap(_root, t._root);
		return *this;
	}


	
	bool Insert(const K& key)	//todo(插入函数: 非递归)
	{
		//*如果树为空，插入的节点就是根
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		//*找到要插入的位置
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
			//*如果发现要插入的值已经存在，则插入失败
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		//*开始插入，判断是在左边还是右边插入
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

	
	bool InsertR(const K& key)	//todo(递归式插入)
	{
		return _InsertR(_root, key);
	}

	
	void InOrder()	//todo(中序遍历)
	{
		_InOrder(_root);
		cout << endl;
	}

	
	Node* Find(const K& key) //todo(查找函数)
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

	
	Node* FindR(const K& key)	//todo(递归式查找)
	{
		return _FindR(_root, key);
	}

	
	bool Erase(const K& key)	//todo(搜索二叉树的删除)
	{
		//*首先找到要删除的结点
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
				//*找到了要删除的结点，准备开始删除
				//*对要删除的结点分为三种情况：
				//*1.节点的左为空  2，结点的右为空  3.结点的左右都不为空
				if (cur->_left == nullptr) 
				{
					if (cur == _root) //!要删除的结点是根节点时要单独处理
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

				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;	//!要删除的结点是根节点时要单独处理
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

				else
				{
					//*要删除的结点的左右都不为空，可以找到左子树最大的结点或者右子树最小的结点去替换要删除的结点
					Node* leftmax_parent = cur;
					Node* leftmax = cur->_left;
					while (leftmax->_right != nullptr) 
					{
						leftmax_parent = leftmax;
						leftmax = leftmax->_right;
					}

					cur->_key = leftmax->_key;	//*用左边最大的结点替换要删除的结点
					
					if (leftmax_parent->_right == leftmax)	//*把左边最大的那个节点拿掉
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

	bool EraseR(const K& key)	//todo(递归式删除)
	{
		return _EraseR(_root, key);
	}

private:
	Node* _root;

	void _Destroy(Node* root)	//todo(销毁所有结点)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	Node* _Copy(Node* root)		//todo(拷贝所有节点)
	{
		if (root == nullptr)
			return nullptr;
		Node* newnode = new Node(root->_key);
		newnode->_left = _Copy(root->_left);
		newnode->_right = _Copy(root->_right);
		return newnode;
	}

	void _InOrder(Node* root)	//todo(中序遍历递归子函数)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << ' ';
		_InOrder(root->_right);
	}

	Node* _FindR(Node* root, const K& key)	//todo(递归式查找递归子函数)
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

	bool _InsertR(Node*& root, const K& key)	//todo(递归式插入子函数)
	{                                           //!注意这里参数传指针的引用
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
			//*找到了删除的位置
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