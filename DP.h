#include <iostream>
#include <string>
#include <vector>
#include<windows.h>

using namespace std;

// 给定一个整数数组nums,找到一个具有最大和的连接子数据，返回其最大和
// 如 [-2, 1, -3, 4, -1, 2, 1, -5, 4]
// 输出 6, 连续子数组是 [ 4, -1, 2, 1 ]
int max_sub_array(int* nums, int len)
{
	vector<int> dp(len, 0);
	int maxValue = dp[0] = nums[0];
	for (int i = 1; i < len; i++)
	{
		dp[i] = max(nums[i], dp[i - 1] + nums[i]);
		if (dp[i] > maxValue)
		{
			maxValue = dp[i];
		}
	}

	return maxValue;
}

// 用对数器比较递归求解和DP求解

// 题目2，机器人走路问题，机器人在一条直线上行走，位置标为从0到N，机器人开始位置为Start，目的地为End,  start和end 在 0 到N 范围内，
// 机器人每次往左或往右走一步（在0位置只能往右，在End位置只能往左），机器人在K步后到达End,求一共有多少可能的路径
// 如 : N = 5, S = 2, E = 4, K = 4
// 可能路径有 2 > 3 > 4 > 5 > 4, 2 > 3 > 2 > 3 > 4 ...　
// 1。 用递归求解

int robot_walk_r(int num, int start, int end, int step)
{
	if (step == 0)
	{
		return start == end ? 1 : 0;
	}

	if (end == 0)
	{
		return robot_walk_r(num, start, 1, step - 1);
	}
	else if (end == num)
	{
		return robot_walk_r(num, start, num - 1, step - 1);
	}

	return robot_walk_r(num, start, end - 1, step - 1) + robot_walk_r(num, start, end + 1, step - 1);
}
 
// 2。 用DP求解
int robot_walk_dp(int num, int start, int end, int step)
{
	// init
	int** array = new int*[num+1];
	for (int i = 0; i <= num; i++)
	{
		array[i] = new int[step + 1];
		for (int j = 0; j <= step; j++)
		{
			array[i][j] = 0;
		}
	}

	// assign
	array[start][0] = 1;
	for (int j = 1; j <= step; j++)
	{
		for (int i = 0; i <= num; i++)
		{
			if (i == 0)
			{
				array[i][j] = array[i + 1][j - 1];
			}
			else if (i == num)
			{
				array[i][j] = array[i - 1][j - 1];
			}
			else
			{
				array[i][j] = array[i + 1][j - 1] + array[i - 1][j - 1];;
			}
		}
	}

	int result = array[end][step];

	// delete
	for (int i = 0; i <= num; i++)
	{
		delete[] array[i];
	}

	delete[] array;

	return result;
}

// 题目3。硬币问题，有一个数组记录每个硬币的面值，求组成总和为N的硬币的最少个数,每个硬币只能用一次
// 如：［2, 3, 5, 3, 7]  n= 10
// 最少个数为2, 3 + 7 = 10

// 1。 用递归求解
int coin_r_impl(int* coins, int len, int index, int remaining) 
{
	if (remaining == 0)
	{
		return 0;
	}

	if (index >= len)
	{
		return len+1; // not exist
	}

	if (remaining < 0)
	{
		return len+1;
	}

	return min(coin_r_impl(coins, len, index + 1, remaining), 
		       coin_r_impl(coins, len, index + 1, remaining - coins[index]) + 1);
}

int coin_r(int* coins, int len, int sum)
{
	int ret = coin_r_impl(coins, len, 0, sum);

	return ret > len ? -1 : ret;
}

// 2。 用DP求解
// 
// 
int coin_dp(int* coins, int len, int sum)
{
	const int MAX_VALUE = len + 1;

	// init
	int** table = new int*[len + 1];
	for (int i = 0; i <= len; i++)
	{
		table[i] = new int[sum + 1];
		table[i][0] = 0; // the column 0 are all 0
		for (int j = 1; j <= sum; j++) 
		{
			table[i][j] = MAX_VALUE;
		}
	}

	for (int i = len - 1; i >= 0; i--)
	{
		for (int j = 1; j <= sum; j++)
		{
			int chooseI = MAX_VALUE;
			if (j - coins[i] >= 0)
			{
				chooseI = table[i + 1][j - coins[i]];
			}

			table[i][j] = min(table[i + 1][j], 1 + chooseI);
			//cout << "i: " << i << " j: " << j << " value: " << table[i][j] << endl;
		}
	}

	int result = table[0][sum] >= MAX_VALUE ? -1 : table[0][sum];

	// delete
	for (int i = 0; i <= len; i++)
	{
		delete[] table[i];
	}
	
	delete[] table;

	return result;
}

// 题目4，马走日问题。（机器人问题3维进阶版） 在象棋棋盘里.宽为9长为10，马在(0,0)位置，求到达(X,Y)位置，步数要求为K，共有多少种走法
// 
// 1。 用递归求解

int house_run_r(int length, int width, int posX, int posY, int targetX, int targetY, int step)
{
	if (posX < 0 || posX > width - 1)
	{
		return 0;
	}

	if (posY < 0 || posY > length - 1)
	{
		return 0;
	}

	if (step == 0)
	{
		if (posX == targetX && posY == targetY)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	return house_run_r(length, width, posX + 2, posY + 1, targetX, targetY, step - 1) +
		house_run_r(length, width, posX + 2, posY - 1, targetX, targetY, step - 1) +
		house_run_r(length, width, posX - 2, posY + 1, targetX, targetY, step - 1) +
		house_run_r(length, width, posX - 2, posY - 1, targetX, targetY, step - 1) +
		house_run_r(length, width, posX + 1, posY + 2, targetX, targetY, step - 1) +
		house_run_r(length, width, posX + 1, posY - 2, targetX, targetY, step - 1) +
		house_run_r(length, width, posX - 1, posY + 2, targetX, targetY, step - 1) +
		house_run_r(length, width, posX - 1, posY - 2, targetX, targetY, step - 1);
}

// 2。 用DP求解
// 

int hourse_run_check(int*** dp, int length, int width, int posX, int posY, int step)
{
	if (posX < 0 || posX > width - 1)
	{
		return 0;
	}

	if (posY < 0 || posY > length - 1)
	{
		return 0;
	}

	return dp[posX][posY][step];
}

int house_run_dp(int length, int width, int posX, int posY, int targetX, int targetY, int step)
{ 
	// init
	int*** dp = new int** [width];
	for (int i = 0; i < width; i++)
	{
		dp[i] = new int* [length];
		for (int j = 0; j < length; j++)
		{
			dp[i][j] = new int[step+1];
			for (int k = 0; k < step + 1; k++)
			{
				dp[i][j][k] = 0;
			}
		}
	}

	dp[targetX][targetY][0] = 1;

	for (int k = 1; k <= step; k++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < length; j++)
			{
				dp[i][j][k] = hourse_run_check(dp, length, width, i + 2, j + 1, k - 1) +
					hourse_run_check(dp, length, width, i + 2, j - 1, k - 1) +
					hourse_run_check(dp, length, width, i - 2, j + 1, k - 1) +
					hourse_run_check(dp, length, width, i - 2, j - 1, k - 1) +
					hourse_run_check(dp, length, width, i + 1, j + 2, k - 1) +
					hourse_run_check(dp, length, width, i + 1, j - 2, k - 1) +
					hourse_run_check(dp, length, width, i - 1, j + 2, k - 1) +
					hourse_run_check(dp, length, width, i - 1, j - 2, k - 1);
			}
		}
	}

	int ret = dp[0][0][step];

	// delete
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			delete[] dp[i][j];
		}
		delete[] dp[i];
	}

	delete[] dp;

	return ret;
}


// 题目5，硬币问题升级版，有一个数组记录每个硬币的面值，每个面值的硬币可使用无限个，求组成总和为N的硬币的方法数
// 
// 1。 用递归求解

int coin_2_r_impl(int* coins, int len, int index, int remaining)
{
	if (remaining < 0)
	{
		return 0;
	}
	else if (remaining == 0)
	{
		return 1;
	}

	if (index > len - 1)
	{
		return 0;
	}

	int maxCount = remaining / coins[index]; // how many current coin can be used
	int result = 0;
	for (int i = 0; i <= maxCount; i++)
	{
		result += coin_2_r_impl(coins, len, index + 1, remaining - i * coins[index]);
	}

	return result;
}

int coin_2_r(int* coins, int len, int target)
{
	return coin_2_r_impl(coins, len, 0, target);
}

// 2。 用DP求解 （要用斜率优化）
// 

int coin_2_check(int** dp, int i, int j)
{
	if (i < 0 || j < 0)
	{
		return 0;
	}

	return dp[i][j];
}

int coin_2_dp(int* coins, int len, int target)
{
	// init
	int** dp = new int* [len + 1];
	for (int i = 0; i <= len; i++)
	{
		dp[i] = new int[target + 1];
		dp[i][0] = 1; // all the column 0 are 1
		for (int j = 1; j <= target; j++)
		{
			dp[i][j] = 0;
		}
	}

	for (int i = len - 1; i >= 0; i--)
	{
		for (int j = 1; j <= target; j++)
		{
			dp[i][j] = coin_2_check(dp, i, j - coins[i]) + dp[i + 1][j];
		}
	}

	int result = dp[0][target];

	// delete
	for (int i = 0; i <= len; i++)
	{
		delete[] dp[i];
	}

	delete[] dp;


	return result;
}

int random(int start, int end)
{
	int range = end - start + 1;
	
	return rand() % range + start;
}


void test_max_sub_array()
{
	srand((unsigned)time(NULL));

	int nums[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	int maxValue = max_sub_array(nums, sizeof(nums) / sizeof(int));
	cout << "the max value is: " <<  to_string(maxValue) << endl;

	// robot walk
	//int count = 0;
	//for (int i = 0; i < 1000; i++)
	//{
	//	int num = random(5, 10);
	//	int start = random(0, num);
	//	int end = random(4, num);
	//	int step = random(3, 8);
	//	int result1 = robot_walk_r(num, start, end, step);
	//	int result2 = robot_walk_dp(num, start, end, step);
	//	if (result1 != result2)
	//	{
	//		cout << "Ooops - something goes wrong, num: " << num << " start: " << start << " end: " << end << " step: " << step << endl;
	//		cout << "result 1: " << result1 << " result 2: " << result2 << endl;
	//		break;
	//	}
	//	else if (result1 != 0)
	//	{
	//		count++;
	//	}
	//	Sleep(1);
	//}
	//cout << count << "/1000 is done" << endl;

	// coin problem
	//int coins[5] = { 0 };
	//int count = 0;
	//for (int i = 0; i < 1000; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		coins[j] = random(2, 7);
	//	}
	//	int sum = random(6, 12);

	//	int result1 = coin_r(coins, sizeof(coins) / sizeof(int), sum);
	//	int result2 = coin_dp(coins, sizeof(coins) / sizeof(int), sum);
	//	if (result1 != result2)
	//	{
	//		cout << "Ooops - something goes wrong, sum: " << sum << endl;
	//		cout << "result 1: " << result1 << " result 2: " << result2 << endl;
	//		break;
	//	}
	//	else if (result1 != 0)
	//	{
	//		cout << "result 1: " << result1 << " result 2: " << result2 << endl;
	//		count++;
	//	}
	//}
	//cout << count << "/1000 is done" << endl;

	//// horse run problem
	//int coins[5] = { 0 };
	//int count = 0;
	//for (int i = 0; i < 1000; i++)
	//{
	//	int targetX = random(0, 8);
	//	int targetY = random(0, 9);
	//	int step = random(3, 7);

	//	int result1 = house_run_r(10, 9, 0, 0, targetX, targetY, step);
	//	int result2 = house_run_dp(10, 9, 0, 0, targetX, targetY, step);
	//	if (result1 != result2)
	//	{
	//		cout << "Ooops - something goes wrong, step: " << step << endl;
	//		cout << "result 1: " << result1 << " result 2: " << result2 << endl;
	//		break;
	//	}
	//	else if (result1 != 0)
	//	{
	//		cout << "target: (" << targetX << "," << targetY << ") step: " << step << " result 1: " << result1 << " result 2: " << result2 << endl;
	//		count++;
	//	}
	//}
	//cout << count << "/1000 is done" << endl;

	// advanced coin problem
	int coins[] = { 2, 3, 5 };
	int count = 0;

	for (int i = 0; i < 1000; i++)
	{
		int target = random(5, 20);

		int result1 = coin_2_r(coins, 3, target);
		int result2 = coin_2_dp(coins, 3, target);
		if (result1 != result2)
		{
			cout << "Ooops - something goes wrong" << endl;
			cout << "result 1: " << result1 << " result 2: " << result2 << endl;
			break;
		}
		else if (result1 != 0)
		{
			//cout << "target: " << target << " result 1: " << result1 << " result 2 : " << result2 << endl;
			count++;
		}
	}
	cout << count << "/1000 is done" << endl;
}