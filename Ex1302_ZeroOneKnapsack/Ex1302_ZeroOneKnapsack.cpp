#include <iostream> 
#include <vector>
#include <algorithm>
#include <iomanip>
#include <algorithm>
using namespace std;

// 용량 W를 n가지의 아이템으로 채운 경우 담을 수 있는 총 가치의 최대값 반환
// n가지의 아이템이라는 말의 의미는 아이템 1, 2, ..., n 을 넣을지 말지를 고려했다는 의미
// W가 더 작은 경우, n이 더 작은 경우에 대해 재귀호출하는 구조 -> 표 만들때는 반대 순서로 W이나 n이 더 작은 경우부터 채워나가면 된다는 의미

int RecurZeroOneKnapsack(const vector<int>& weightTable, const vector<int>& valueTable, int limitWeight, int maxItem)
{
	cout << "limitWeight = " << limitWeight << ", numItems = " << maxItem << endl;

	// 인덱싱 주의
	// weightTable[numItems-1] numItems번째 아이템의 무게
	// valueTable[numItems-1]  numItems번째 아이템의 가치(가격)

	if (maxItem == 0 || limitWeight == 0)
	{
		return 0;
	}
	
	// TODO: 용량 W가 부족해서 weights[n - 1]를 넣을 수 없다면
	if (limitWeight < weightTable[maxItem - 1])
	{
		// TODO: n번째 아이템을 넣지 않는 서브트리로 내려감 (용량은 그대로)
		return RecurZeroOneKnapsack(weightTable, valueTable, limitWeight, maxItem - 1);
	}

	// n번째 아이템을 넣지 않는 경우와 넣는 경우 중 더 큰 값
	// Case 1. 넣지 않는 경우: n-1개의 아이템만 고려하는 경우에 대해 재귀호출
	// Case 2. 넣는 경우: n번째 아이템이 들어갈 용량을 미리 빼놓고 (확보해놓고) n-1개의 아이템만 고려하는 경우에 대해 재귀호출
	//                   재귀호출 결과를 그대로 사용하면 안되고 뭔가 더해줘야 합니다.

	return max(RecurZeroOneKnapsack(weightTable, valueTable, limitWeight, maxItem - 1), // Case 1
			   RecurZeroOneKnapsack(weightTable, valueTable, limitWeight - weightTable[maxItem - 1], maxItem - 1) + valueTable[maxItem - 1]); // Case 2
}

int ZeroOneKnapsack(const vector<int>& weightTable, const vector<int>& valueTable, int maxLimitWeight)
{
	//주의: table에서는 1-based, weightTable와 valueTable에서는 0-based 사용
	//     아이템 i의 무게는 weightTable[i - 1] 
	//     아이템 i의 가치는 valueTable[i - 1]
	//     maxValueTable[limitWeight][maxItem] : 무게 제한이 limitWeight이고 아이템을 1 ~ maxItem까지 고려했을 때 최대 가치 (아이템 n만 고려했다는 것이 아니라 1, ..., n을 모두 고려했다는 의미)

	vector<vector<int>> maxValueTable(maxLimitWeight + 1, vector<int>(weightTable.size() + 1, 0)); // 모두 0으로 초기화 (아래 루프에서 w = 0 또는 n = 0인 경우 없음)
	vector<vector<vector<int>>> itemCntTable(maxLimitWeight + 1, vector<vector<int>>(weightTable.size() + 1, vector<int>(weightTable.size(), 0))); // 디버깅 도우미, 출력 예시 참고

	//힌트: RecurZeroOneKnapsack()하고 연관지어서 생각해보세요.

	for (int limitWeight = 1; limitWeight <= maxLimitWeight; limitWeight++)
	{
		for (int maxItem = 1; maxItem <= weightTable.size(); maxItem++)
		{
			// 힌트: 재귀호출 하는 대신에 먼저 계산되어서 maxValueTable에 저장되어 있는 값 사용
			
			// 무게 제한을 넘어서 넣을 수 없는 경우
			if (limitWeight < weightTable[maxItem - 1])
			{
				maxValueTable[limitWeight][maxItem] = maxValueTable[limitWeight][maxItem - 1];
				itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight][maxItem - 1];
			}
			else
			{
				const int valueIncludingMaxItem = maxValueTable[limitWeight - weightTable[maxItem - 1]][maxItem - 1] + valueTable[maxItem - 1];

				// Case 1: 넣지 않는 경우
				if (maxValueTable[limitWeight][maxItem - 1] > valueIncludingMaxItem)
				{
					maxValueTable[limitWeight][maxItem] = maxValueTable[limitWeight][maxItem - 1];
					itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight][maxItem - 1];
				}
				// Case 2: 넣는 경우
				else 
				{
					maxValueTable[limitWeight][maxItem] = valueIncludingMaxItem;
					itemCntTable[limitWeight][maxItem] = itemCntTable[limitWeight - weightTable[maxItem - 1]][maxItem - 1];
					itemCntTable[limitWeight][maxItem][maxItem - 1] += 1; // 안내: 가장 오른쪽 [n-1]은 0-based indexing이라서 -1 추가
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

int main()
{
	const vector<int> valueTable = { 6, 5, 3 };
	const vector<int> weightTable = { 3, 2, 1 };
	const int limitWeight = 5;

	// 전체 용량 limitWeight에 대해 모든 아이템을 고려하는 numItems = weights.size()로 재귀호출 시작
	std::cout << RecurZeroOneKnapsack(weightTable, valueTable, limitWeight, static_cast<int>(weightTable.size())) << endl;

	std::cout << ZeroOneKnapsack(weightTable, valueTable, limitWeight) << endl;

	return 0;
}
