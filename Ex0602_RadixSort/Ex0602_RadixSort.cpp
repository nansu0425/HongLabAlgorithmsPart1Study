#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;

void Print(vector<int>& arr)
{
	for (auto& a : arr)
		cout << a << " ";
	cout << endl;
}

inline size_t getOneDigit(int number, int exp)
{
	return static_cast<size_t>(number / pow(10, exp)) % 10;
}

// 편의상 결과가 arr에 저장되도록 바꿨습니다.
void CountingSort(vector<int>& arr, int k, int exp)
{
	vector<int> temp = arr; // 복사

	vector<int> count(k + 1, 0);
	
	for (int tempIdx = 0; tempIdx < temp.size(); ++tempIdx)
	{
		++count[getOneDigit(temp[tempIdx], exp)];
	}

	for (int countIdx = 1; countIdx < count.size(); ++countIdx)
	{
		count[countIdx] += count[countIdx - 1];
	}

	for (int tempIdx = arr.size() - 1; tempIdx >= 0; tempIdx--)
	{
		size_t digit = getOneDigit(temp[tempIdx], exp);

		--count[digit];
		arr[count[digit]] = temp[tempIdx];
	}
}

void RadixSort(vector<int>& arr)
{
	int k = 9; // 0 이상 9 이하
	int m = *max_element(arr.begin(), arr.end());
	int maxNumDigits = 0;

	for (int maxVal = m; maxVal > 0; maxVal /= 10)
	{
		++maxNumDigits;
	}

	for (int exp = 0; exp < maxNumDigits; ++exp)
	{
		cout << "exp = " << exp << endl;

		CountingSort(arr, k, exp);

		Print(arr);
	}
}

int main()
{
	vector<int> arr = { 170, 45, 75, 90, 802, 24, 2, 66 };
	//vector<int> arr = { 2, 5, 3, 0, 2, 3, 0, 3 };

	Print(arr);

	RadixSort(arr);

	return 0;
}