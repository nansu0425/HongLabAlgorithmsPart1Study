#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <string>
#include <utility>

using namespace std;

template<typename T>
void Print(vector<T>& arr)
{
	for (auto& a : arr)
		cout << a << " ";
	cout << endl;
}

void CountingSort(vector<string>& arr, int k, int charIdx)
{
	vector<string> oldArr = arr; // 복사
	// std::fill(arr.begin(), arr.end(), "   "); // 디버깅 편의

	vector<size_t> counts(k);

	// 문자의 개수 세기
	for (const std::string word : oldArr)
	{
		++counts[word[charIdx] - 'A'];
	}

	// counts 원소로 arr의 인덱스를 계산할 수 있도록 수정
	for (int countsIdx = 1; countsIdx < counts.size(); ++countsIdx)
	{
		counts[countsIdx] += counts[countsIdx - 1];
	}

	// charIdx의 문자 기준으로 oldArr를 정렬하여 arr로 복사
	for (int oldArrIdx = oldArr.size() - 1; oldArrIdx >= 0; --oldArrIdx)
	{
		int countsIdx = oldArr[oldArrIdx][charIdx] - 'A';

		--counts[countsIdx];
		arr[counts[countsIdx]] = oldArr[oldArrIdx];
	}

}

void RadixSort(vector<string>& arr)
{
	for (int charIdx = arr[0].size() - 1; charIdx >= 0; --charIdx)
	{
		CountingSort(arr, 'Z' - 'A' + 1, charIdx);
	}
}

int main()
{
	// CLRS 8.3-1
	vector<string> arr = { "COW", "DOG", "SEA", "RUG",
		"ROW", "MOB", "BOX", "TAB", "BAR", "EAR", "TAR",
		"DIG", "BIG", "TEA", "NOW", "FOX" };

	Print(arr);

	RadixSort(arr);

	Print(arr);

	return 0;
}