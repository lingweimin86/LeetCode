#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Heap
//可转化为完全二叉树且每个父节点的值比子节点大
//如
//			   6
//			  /  \
//			 4    5
//			/ \  / \
//		   3  2  4  3

// 数组形式
//[6, 4, 5, 3, 2, 4, 3]

// 求左子节点: i*2 +1
// 求右子节点: i*2 +2
// 求父节点：　(i - 1) / 2

// Note: 优先级队列，就是大根堆   std::priority_queue

const int HEAP_MAX = 100;

template<typename T>
class Myheap
{
private:
	T _data[HEAP_MAX];
	int _size;

	void heapify();
public:
	Myheap();
	Myheap(vector<T> vec);
	bool push_heap(T value);
	T pop_heap();

	friend ostream& operator<<(ostream& os, Myheap heap)
	{
		cout << "heap: ";
		for (int i = 0; i < heap._size; i++)
		{
			os << to_string(heap._data[i]) << " ";
		}

		cout << "size: " << to_string(heap._size) << endl;
		return os;
	}

	friend void swap(T& lhs, T& rhs)
	{
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}
};

//ostream& operator<<(ostream& os, Myheap<int> heap)
//{
//	cout << "heap: ";
//	for (int i = 0; i < heap._size; i++)
//	{
//		os << to_string(heap._data[i]) << " ";
//	}
//
//	cout << "size: " << to_string(heap._size) << endl;
//	return os;
//}

template<typename T>
Myheap<T>::Myheap()
{
	memset(_data, 0, sizeof(_data));
	_size = 0;
}

template<typename T>
Myheap<T>::Myheap(vector<T> vec)
{
	memset(_data, 0, sizeof(_data));
	_size = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		push_heap(vec[i]);
	}
}

// 将元素放置尾部，与父节点进行比较，如果大于父点子则交换，重复此步骤
// insert heap
template<typename T>
bool Myheap<T>::push_heap(T value)
{
	if (_size == HEAP_MAX)
	{
		return false;
	}

	_data[_size++] = value;
	int i = _size - 1;
	int parent = (i - 1) / 2;
	while (_data[i] > _data[parent])
	{
		// swap
		//T temp = _data[i];
		//_data[i] = _data[parent];
		//_data[parent] = temp;
		swap(_data[i], _data[parent]);

		i = parent;
		parent = (i - 1) / 2;
	}

	return true;
}

// 1。返回头元素
// 2。将尾元素放至头元素，size减一, 然后取左右子节点的最大值，与之比较，如果比当前节点大，则交换，重复此步骤

template<typename T>
T Myheap<T>::pop_heap()
{
	if (_size == 0)
		return -1;

	int top = _data[0];
	_size--;

	//heapify
	heapify();

	return top;
}

template<typename T>
void Myheap<T>::heapify()
{
	// heapify
	if (_size > 0)
	{
		swap(_data[0], _data[_size]); // swap the first and last element
		int index = 0; // parent node
		int left = 1; // left child node 
		while (left < _size)
		{
			int right = left + 1; // right child node
			int largest = (right < _size && _data[right] > _data[left] ? right : left);

			largest = _data[largest] > _data[index] ? largest : index;
			if (largest == index)
			{
				break;
			}

			// swap
			//T temp = _data[largest];
			//_data[largest] = _data[index];
			//_data[index] = temp;
			swap(_data[largest], _data[index]);

			index = largest;
			left = index * 2 + 1;
		}
	}
}

//ostream& operator<<(ostream& os, Myheap<int> heap);

void test_heap()
{
	vector<int> vec { 3, 5, 6, 2, 1 };
	Myheap<int> myheap(vec);

	cout << "original: " << myheap;

	myheap.push_heap(7);

	cout << "insert 7: " << myheap;

	int top = myheap.pop_heap();

	cout << "pop the top: " << myheap;
}

