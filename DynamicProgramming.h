#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

#define SIZE 7
#define COST 6 // days

// ��ǰ��Ԫ���ֵ = 
// A. ��ǰ��Ʒ�޷����뵱ǰ��Ԫ�� ��һ����Ԫ���ֵ ����һ�У�ͬ�У�
// B�����Է���Ļ��������������������ֵ 
//       B1.��һ����Ԫ���ֵ ����һ�У�ͬ�У�
//       B2.��ǰ��Ʒ�ļ�ֵ + ʣ��ռ�ļ۸� ����һ�У������У�


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


// ֻ��һά����ʵ�֣��±���cost,ֵ��value������Ϊsize
void DynamicProgramming_r(const Element* elements)
{
	int array[COST+1]{0}; // ����һ��Ĭ��Ϊ0

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
	// ȱ�㣬�����ҳ�Ԫ�صļ���
}

void test_DynamicProgramming()
{
	const Element elements[] = {
	    Element { 0, "�찲�Ź㳡", 1, 9 },
		Element { 1, "�ʹ�", 4, 9 },
		Element { 2, "�ú�԰", 2, 9},
		Element { 3, "�˴��볤��", 1, 7},
		Element { 4, "��̳", 1, 6},
		Element { 5, "Բ��԰", 2, 8},
		Element { 6, "������", 1, 5},
	};

	//constexpr int size = sizeof(elements) / sizeof(Element);
	//const int cost = 6; // total days 

	DynamicProgramming_r(elements);


}
