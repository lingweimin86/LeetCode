#include <unordered_map>
#include <iostream>
#include <string>

// 爬楼梯，一次能爬一步或二步，输入阶梯数，求解法

using namespace std;

unordered_map<int, int> stairs;

int climb_stairs(int steps)
{
	if (steps == 1)
		return 1;
	else if (steps == 2)
		return 2;
	else if (stairs.contains(steps))
	{
		return stairs.at(steps);
	}
	else
	{
		int result = climb_stairs(steps - 1) + climb_stairs(steps - 2);
		stairs[steps] = result;
		return result;
	}
}

void test_climb_stairs()
{
	int s1 = 10;
	cout << "input : " << s1 << endl;
	int actual1 = climb_stairs(s1);
	cout << "output : " << to_string(actual1) << endl;

	int s2 = 30;
	cout << "input : " << s2 << endl;
	int actual2 = climb_stairs(s2);
	cout << "output : " << to_string(actual2) << endl;
}