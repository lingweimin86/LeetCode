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

	// ������ڴ�й©����Ϊpa->m_B��pb->m_A��ָ��
	// ����취����pa->m_B��pb->m_A����һ��Ϊweak_ptr
}