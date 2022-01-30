#include<iostream>
#include<vector>
#include<time.h>
using std::cout;
using std::endl;

#ifdef _WIN32
#include<windows.h>
#else
// 
#endif

//ֱ��ȥ���ϰ�ҳ����ռ�
inline static void* SystemAlloc(size_t kpage)
{
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
//linux��brk mmap��
#endif
	if (ptr == nullptr)
		throw std::bad_alloc();
	return ptr;
}

template<class T>
class FixedPool
{
private:
	char* _memory = nullptr; //ָ����ڴ���ָ��
	size_t _remainSize = 0; //���ڴ��ʣ��ɷ�����ֽ���
	void* _freeList = nullptr; //���������ͷָ��
public:
	T* New() //�����ڴ�
	{
		T* obj = nullptr;

		if (_freeList) //�����������Ϊ�գ������ȷ�����յ��ڴ�
		{
			void* next = *(void**)_freeList;
			obj = (T*)_freeList;
			_freeList = next;
		}
		else //�ڴ��ڴ�����з��ڴ�
		{
			if (_remainSize < sizeof(T)) //ʣ��ռ䲻�㣬��Ҫ�ڿ���һ����ڴ��
			{
				_remainSize = 128 * 1024; //128k
				//_memory = (char*)malloc(_remainSize);
				_memory = (char*)SystemAlloc(_remainSize >> 13); //ֱ��ȥ��������ռ�

				if (_memory == nullptr)
				{
					throw std::bad_alloc();
				}
			}

			obj = (T*)_memory; //�����ڴ�
			size_t objSize = sizeof(T) > sizeof(void*) ? sizeof(T) : sizeof(void*); //��֤�ռ���Դ洢��һ����ַ
			_memory += objSize; //���ڴ��ͷ��ָ���ƶ�
			_remainSize -= objSize; //���ڴ��ʣ��ɷ�����ֽ�������
		}

		new(obj)T; //��λnew,��ʽ����T�Ĺ��캯����ʼ��

		return obj;
	}

	void Delete(T* obj)
	{
		obj->~T(); //��ʽ������������

		*(void**)obj = _freeList; //ͷ��
		_freeList = obj;
	}
};

struct TreeNode
{
	int _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}
};