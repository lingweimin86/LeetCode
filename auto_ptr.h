#include <memory>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class B;

class A
{
public:
	shared_ptr<B> m_B;
};

class B
{
public:
	// shared_ptr<A> m_A;
	weak_ptr<A> m_A;
};


void test_shared_pointer()
{
	{
		shared_ptr<A> pa(new A);
		shared_ptr<B> pb(new B);
		
		pa->m_B = pb;
		pb->m_A = pa;

		cout << to_string(pa.use_count()) << endl;
		cout << to_string(pb.use_count()) << endl;
	}

	// 会造成内存泄漏，因为pa->m_B和pb->m_A互指了
	// 解决办法，让pa->m_B和pb->m_A其中一个为weak_ptr
}