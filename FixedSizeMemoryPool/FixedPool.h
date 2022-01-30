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

//直接去堆上按页申请空间
inline static void* SystemAlloc(size_t kpage)
{
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
//linux下brk mmap等
#endif
	if (ptr == nullptr)
		throw std::bad_alloc();
	return ptr;
}

template<class T>
class FixedPool
{
private:
	char* _memory = nullptr; //指向大内存块的指针
	size_t _remainSize = 0; //大内存块剩余可分配的字节数
	void* _freeList = nullptr; //自由链表的头指针
public:
	T* New() //分配内存
	{
		T* obj = nullptr;

		if (_freeList) //如果自由链表不为空，则优先分配回收的内存
		{
			void* next = *(void**)_freeList;
			obj = (T*)_freeList;
			_freeList = next;
		}
		else //在大内存块中切分内存
		{
			if (_remainSize < sizeof(T)) //剩余空间不足，需要在开辟一块大内存块
			{
				_remainSize = 128 * 1024; //128k
				//_memory = (char*)malloc(_remainSize);
				_memory = (char*)SystemAlloc(_remainSize >> 13); //直接去堆上申请空间

				if (_memory == nullptr)
				{
					throw std::bad_alloc();
				}
			}

			obj = (T*)_memory; //分配内存
			size_t objSize = sizeof(T) > sizeof(void*) ? sizeof(T) : sizeof(void*); //保证空间可以存储下一个地址
			_memory += objSize; //大内存块头部指针移动
			_remainSize -= objSize; //大内存块剩余可分配的字节数减少
		}

		new(obj)T; //定位new,显式调用T的构造函数初始化

		return obj;
	}

	void Delete(T* obj)
	{
		obj->~T(); //显式调用析构函数

		*(void**)obj = _freeList; //头插
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