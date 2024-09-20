#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> arr = { 8, 2, 3, 5, 9, 1, 9, 4, 3, 7, 6, 7 };

	// swap에 필요한 비교 연산: 1
	if (arr[0] > arr[1])
	{
		std::swap(arr[0], arr[1]);
	}

	for (int arrIdx = 2; arrIdx < arr.size(); arrIdx += 2)
	{
		// swap에 필요한 비교 연산: n/2 - 1
		if (arr[arrIdx] > arr[arrIdx + 1])
		{
			std::swap(arr[arrIdx], arr[arrIdx + 1]);
		}

		// 최솟값 결정을 위해 필요한 비교 연산: n/2 - 1
		arr[0] = std::min(arr[0], arr[arrIdx]);
		// 최댓값 결정을 위해 필요한 비교 연산: n/2 - 1
		arr[1] = std::max(arr[1], arr[arrIdx + 1]);
	}

	cout << "Min value = " << arr[0] << ", Max value = " << arr[1] << endl; // Min value = 1, Max value = 9
}
