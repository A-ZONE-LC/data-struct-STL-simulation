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


	//1.����
	//�ǵݹ�
	bool Insert(const K& key)
	{
		//_rootΪ�գ�ֱ�Ӹ���_root
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		//�������±�����key��cur��_key������ң�С������
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
			//��Ⱦ�return false
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		//�ҵ��˺��ʵ�λ�ã��ж�������������
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

	//�ݹ�
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	//2.�������
	void InOrder()
	{
		//Ϊ�˵��õ�ʱ�򲻴�����
		_InOrder(_root);
		cout << endl;
	}

	//3.����
	//�ǵݹ�
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

	//�ݹ�
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	//4.ɾ��
	//�ǵݹ�
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
				//�ҵ��ˣ�׼��ɾ��
				//(1) cur������ǿգ���parentָ��cur���ұ�
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
				//(2) cur���ұ��ǿգ���parentָ��cur�����
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
				//(3) cur�����߶���Ϊ��
				else
				{
					//�ҵ��������
					Node* leftmax_parent = cur;//���ﲻ����nullptr�����leftmax->rightΪ�գ�����ȥѭ��leftmax_parentʼ��Ϊnullptr,��������
					Node* leftmax = cur->_left;
					while (leftmax->_right != nullptr)
					{
						leftmax_parent = leftmax;
						leftmax = leftmax->_right;
					}
					//���ҵ������ֵleftmax�滻cur,��ɾ��leftmax
					cur->_key = leftmax->_key;
					
					//������if(leftmax->_left == nullptr)
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
		//Node*& root �ı�root��ͬʱҲ�ı����ϼ���root->_left����root->_right
		//root ��root->_left����root->_right�ı���
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
			//ɾ��
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