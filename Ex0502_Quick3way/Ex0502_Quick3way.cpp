#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

void Print(vector<int>& arr, int lo, int hi, string sep = "")
{
	//cout << "Index: ";
	//for (int i = 0; i < arr.size(); i++)
	//	cout << setfill(' ') << setw(3) << i;
	//cout << endl;

	cout << "Value: ";
	for (int i = 0; i < arr.size(); i++) {

		if (lo <= i && i <= hi)
			cout << setfill(' ') << setw(3) << arr[i] << sep;
		else
			cout << "   ";
	}
	cout << endl;
}

// Quicksort with 3-way partitioning, Sedgewick p299
// (Dijkstra's Dutch national flag problem)
void Quick3way(vector<int>& arr, int leftIdx, int rightIdx)
{
	if (rightIdx <= leftIdx) 
	{
		return;
	}

	int highIdx = leftIdx;
	int lowIdx = leftIdx;
	int pivotVal = arr[leftIdx];

	for (int compIdx = leftIdx + 1; compIdx <= rightIdx; ++compIdx)
	{
		// 비교 원소가 피벗 원소보다 작은 경우
		if (arr[compIdx] < pivotVal)
		{
			// 피벗보다 큰 원소가 있는 경우
			if (highIdx < compIdx - 1)
			{
				std::swap(arr[lowIdx], arr[highIdx + 1]);
			}

			std::swap(arr[lowIdx], arr[compIdx]);
			++lowIdx;
			++highIdx;
		}
		// 비교 원소와 피벗 값이 같은 경우
		else if (arr[compIdx] == pivotVal)
		{
			++highIdx;
			std::swap(arr[highIdx], arr[compIdx]);
		}
	}

	Print(arr, leftIdx, rightIdx);

	Quick3way(arr, leftIdx, lowIdx - 1);
	Quick3way(arr, highIdx + 1, rightIdx);
}

int main()
{
	srand(0);

	vector<int> arr = { 3, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 2, 3, 4, 5, 1, 3, 5 };

	Print(arr, 0, arr.size() - 1);

	Quick3way(arr, 0, arr.size() - 1);

	Print(arr, 0, arr.size() - 1);

	return 0;
}
