#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

#define SIZE 7
#define COST 6 // days

// 当前单元格的值 = 
// A. 当前商品无法放入当前单元格， 上一个单元格的值 （上一行，同列）
// B。可以放入的话，考虑以下两者中最大值 
//       B1.上一个单元格的值 （上一行，同列）
//       B2.当前商品的价值 + 剩余空间的价格 （上一行，其他列）


struct Element {
	int id;
	string name;
	int cost;
	int value;
};

int GetSumValue(set<int>* ids, const Element* elements)
{
	int value = 0;
	for (const auto& id : *ids)
	{
		value += elements[id].value;
	}
	return value;
}
   
void DynamicProgramming(const Element* elements)
{
	set<int> array[SIZE][COST];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < COST; j++)
		{
			if (i == 0) {
				array[i][j].insert(elements[0].id); // set default 
			}
			else
			{
				int preRow = i - 1;
				int currCost = j + 1;
				const Element* currEle = &elements[i];
				if (currEle->cost > currCost) 
				{
					array[i][j].insert(array[preRow][j].begin(), array[preRow][j].end()); //Case A
				}
				else
				{
					int costLeft = currCost - currEle->cost;
					int value = currEle->value;
					if (costLeft >= 1)
					{
						value += GetSumValue(&array[preRow][costLeft - 1], elements);
					}
					int valuePreRow = GetSumValue(&array[preRow][j], elements);

					if (valuePreRow > value)
					{
						array[i][j].insert(array[preRow][j].begin(), array[preRow][j].end()); //Case B1
					}
					else
					{ // Case B2
						if (costLeft == 0)
						{
							array[i][j].insert(currEle->id);
						}
						else
						{
							array[i][j].insert(array[preRow][costLeft - 1].begin(), array[preRow][costLeft - 1].end());
							array[i][j].insert(currEle->id);
						}
					}
				}
			}

		}
	}

	cout << "the best choices are: ";
	for (const int id : array[SIZE-1][COST-1])
	{
		cout << elements[id].name << ", ";
	}
	cout << endl;
	cout << "the score is: " << to_string(GetSumValue(&array[SIZE-1][COST-1], elements)) << endl;
}


// 只用一维数组实现，下标是cost,值是value，长度为size
void DynamicProgramming_r(const Element* elements)
{
	int array[COST+1]{0}; // 增加一行默认为0

	for (int i = 1; i < SIZE + 1; i++)
	{
		const Element* currEle = &elements[i-1];
		for (int j = COST; j > 0; j--)
		{
			int currCost = j;
			if (currCost >= currEle->cost)
			{
				int value = currEle->value;
				if (currCost - currEle->cost > 0)
				{
					value += array[currCost - currEle->cost];
				}

				array[currCost] = max(value, array[currCost]);
			}
			else
			{
				break;
			}
		}
	}

	cout << "the score is: " << to_string(array[COST]) << endl;
	// 缺点，不能找出元素的集合
}

void test_DynamicProgramming()
{
	const Element elements[] = {
	    Element { 0, "天安门广场", 1, 9 },
		Element { 1, "故宫", 4, 9 },
		Element { 2, "颐和园", 2, 9},
		Element { 3, "八达岭长城", 1, 7},
		Element { 4, "天坛", 1, 6},
		Element { 5, "圆明园", 2, 8},
		Element { 6, "恭王府", 1, 5},
	};

	//constexpr int size = sizeof(elements) / sizeof(Element);
	//const int cost = 6; // total days 

	DynamicProgramming_r(elements);


}
