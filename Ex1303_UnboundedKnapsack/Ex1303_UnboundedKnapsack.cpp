#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template<typename T>
void Print(const vector<T>& items)
{
	for (auto v : items)
	{
		cout << setw(3) << v;
	}
	cout << endl;
}

//  무게 제한이 limitWeight일 때 1 ~ maxItem까지 고려한 최대 가치
int RecurUnboundedKnapsack(const vector<int>& weightTable, const vector<int>& valueTable, int limitWeight, int maxItem)
{
	// RecurZeroOneKnapsack()와 동일한 코드입니다.
	// Unbounded 버전으로 수정해보세요.
	// 힌트: maxItem을 여러 번 넣을 수 있다.

	cout << "limitWeight = " << limitWeight << ", maxItem = " << maxItem << endl;

	if (maxItem == 0 || limitWeight == 0)
	{
		return 0;
	}

	if (weightTable[maxItem - 1] > limitWeight)
	{
		return RecurUnboundedKnapsack(weightTable, valueTable, limitWeight, maxItem - 1);
	}
	
	
	return max(RecurUnboundedKnapsack(weightTable, valueTable, limitWeight, maxItem - 1), // maxItem 넣지 않는 경우
			   RecurUnboundedKnapsack(weightTable, valueTable, limitWeight - weightTable[maxItem - 1], maxItem) + valueTable[maxItem - 1]); // maxItem 넣는 경우
	
}

// ZeroOneKnapsack()을 아주 약간만 수정한 버전
int BottomUpUnboundedKnapsack1(vector<int> weightTable, vector<int> valueTable, int maxLimitWeight)
{
	vector<vector<int>> maxValueTable(maxLimitWeight + 1, vector<int>(weightTable.size() + 1, 0)); // 모두 0으로 초기화 (아래 루프에서 w = 0 또는 n = 0인 경우 없음)
	vector<vector<vector<int>>> itemCntTable(maxLimitWeight + 1, vector<vector<int>>(weightTable.size() + 1, vector<int>(weightTable.size(), 0)));

	for (int limitWeight = 1; limitWeight <= maxLimitWeight; limitWeight++)
	{
		for (int maxItem = 1; maxItem <= weightTable.size(); maxItem++)
		{
			// maxItem이 한계 무게를 초과하는 경우 maxItem을 제외
			if (weightTable[maxItem - 1] > limitWeight)
			{
				maxValueTable[limitWeight][maxItem] = maxValueTable[limitWeight][maxItem - 1];
				itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight][maxItem - 1];
			}
			else
			{
				const int valueIncludingMaxItem = maxValueTable[limitWeight - weightTable[maxItem - 1]][maxItem] + valueTable[maxItem - 1];

				// maxItem을 포함하지 않은 가치가 maxItem을 포함한 가치보다 더 높은 경우
				if (maxValueTable[limitWeight][maxItem - 1] > valueIncludingMaxItem)
				{
					maxValueTable[limitWeight][maxItem] = maxValueTable[limitWeight][maxItem - 1];
					itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight][maxItem - 1];
				}
				else
				{
					maxValueTable[limitWeight][maxItem] = valueIncludingMaxItem;
					itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight - weightTable[maxItem - 1]][maxItem];
					itemCntTable[limitWeight][maxItem][maxItem - 1] += 1;
				}
			}
		}
	}

	using std::cout;

	cout << maxValueTable[maxLimitWeight][weightTable.size()] << endl;
	for (int i = 0; i <= weightTable.size(); i++)
	{
		cout << i << ": ";
		for (int w = 0; w <= maxLimitWeight; w++)
			cout << right << setw(4) << maxValueTable[w][i];
		cout << endl;
	}
	cout << endl;

	cout << "Weight:";
	for (int w = 0; w <= maxLimitWeight; w++)
		cout << right << setw(4) << w;
	cout << endl << endl;

	cout << "Items count" << endl;
	for (int i = 0; i <= weightTable.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= maxLimitWeight; w++) {
			for (int j = 0; j < weightTable.size(); j++)
				cout << itemCntTable[w][i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Values per item" << endl;
	for (int i = 0; i <= weightTable.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= maxLimitWeight; w++) {
			for (int j = 0; j < weightTable.size(); j++)
				cout << itemCntTable[w][i][j] * valueTable[j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Weights per item" << endl;
	for (int i = 0; i <= weightTable.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= maxLimitWeight; w++) {
			for (int j = 0; j < weightTable.size(); j++)
				cout << itemCntTable[w][i][j] * weightTable[j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	return maxValueTable[maxLimitWeight][weightTable.size()];
}

int BottomUpUnboundedKnapsack2(vector<int> weightTable, vector<int> valueTable, int maxLimitWeight)
{
	vector<int> maxValueTable(maxLimitWeight + 1, 0); // 1차원 배열 (ZeroOne에서는 2차원)
	vector<vector<int>> itemCntTable(maxLimitWeight + 1, vector<int>(weightTable.size(), 0));

	for (int limitWeight = 1; limitWeight <= maxLimitWeight; limitWeight++)
	{
		for (int maxItem = 1; maxItem <= weightTable.size(); maxItem++)
		{
			// maxItem을 포함시킬 수 있는 경우
			if (weightTable[maxItem - 1] <= limitWeight)
			{
				const int valueIncludingMaxItem = maxValueTable[limitWeight - weightTable[maxItem - 1]] + valueTable[maxItem - 1];

				// maxItem을 포함한 가치가 더 큰 경우
				if (maxValueTable[limitWeight] < valueIncludingMaxItem)
				{
					maxValueTable[limitWeight] = valueIncludingMaxItem;
					itemCntTable[limitWeight] = itemCntTable[limitWeight - weightTable[maxItem - 1]];
					++itemCntTable[limitWeight][maxItem - 1];
				}
			}
		}

		cout << "Weight " << setw(2) << limitWeight << ", " << "Value " << setw(2) << maxValueTable[limitWeight] << ", items: ";
		Print(itemCntTable[limitWeight]);
	}

	cout << "Items  : ";
	Print(itemCntTable[maxLimitWeight]);
	int wsum = 0, vsum = 0;
	for (int i = 0; i < weightTable.size(); i++)
	{
		wsum += weightTable[i] * itemCntTable[maxLimitWeight][i];
		vsum += valueTable[i] * itemCntTable[maxLimitWeight][i];
	}
	cout << wsum << " " << vsum << endl;

	return maxValueTable[maxLimitWeight]; // W만큼 채웠을 때 가격의 합
}

int main()
{
	//int limitWeight = 20; // 30
	// vector<int> weightTable = { 1, 2, 3 };
	// vector<int> valueTable = { 1, 3, 2 };

	int limitWeight = 10; // 42
	vector<int> weightTable = { 6, 2,  4,  3, 11 };
	vector<int> valueTable = { 20, 8, 14, 13, 35 };

	{
		cout << "Brute-force Recursion" << endl;
		cout << "limitWeight = " << limitWeight << endl;
		cout << "weightTable: ";
		Print(weightTable);
		cout << "valueTable : ";
		Print(valueTable);
		vector<int> result(weightTable.size(), 0);
		cout << RecurUnboundedKnapsack(weightTable, valueTable, limitWeight, int(weightTable.size())) << endl;
		cout << endl;
	}

	{
		cout << "Bottom-up Tabulation" << endl;
		cout << "limitWeight = " << limitWeight << endl;
		cout << "weightTable: ";
		Print(weightTable);
		cout << "valueTable : ";
		Print(valueTable);

		cout << BottomUpUnboundedKnapsack1(weightTable, valueTable, limitWeight) << endl;
		cout << endl;

		cout << BottomUpUnboundedKnapsack2(weightTable, valueTable, limitWeight) << endl;
		cout << endl;
	}

	return 0;
}
