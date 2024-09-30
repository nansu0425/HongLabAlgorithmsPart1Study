#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;

// CLRS 4판 14.1 Rod Cutting

int RecurCutRod(const vector<int>& prices, int length)
{
	if (length == 0)
		return 0; // return length* prices[0];

	int max_price = numeric_limits<int>::min();

	for (int cutLength = 1; cutLength <= length; cutLength++)
	{
		int price = 0;
		int cutLengthPrice = (cutLength == length) ? prices[length] : RecurCutRod(prices, cutLength);
		int leftLength = length;

		while (leftLength - cutLength >= 0)
		{
			leftLength -= cutLength;
			price += cutLengthPrice;
		}

		if (leftLength > 0)
		{
			price += RecurCutRod(prices, leftLength);
		}

		max_price = std::max(max_price, price);
	}

	return max_price;
}

int MemoizedCutRodHelper(const vector<int>& prices, int length, vector<int>& memo)
{
	if (memo[length] >= 0)
		return memo[length];

	for (int cutLength = 1; cutLength <= length; ++cutLength)
	{
		int price = 0;
		int cutLengthPrice = (cutLength == length) ? prices[length] : MemoizedCutRodHelper(prices, cutLength, memo);
		int leftLength = length;

		while (leftLength - cutLength >= 0)
		{
			leftLength -= cutLength;
			price += cutLengthPrice;
		}

		if (leftLength > 0)
		{
			price += MemoizedCutRodHelper(prices, leftLength, memo);
		}

		memo[length] = std::max(memo[length], price);
	}

	for (auto& t : memo) cout << setw(3) << t; cout << endl;

	return memo[length];
}

int MemoizedCutRod(const vector<int>& prices, int length)
{
	vector<int> memo(length + 1, -1);
	memo[0] = 0;

	return MemoizedCutRodHelper(prices, length, memo);
}

int BottomUpCutRod(const vector<int>& prices, int length)
{
	vector<int> table(length + 1, -1); // 가격은 음수가 될 수 없으니까 디버깅 편의를 위해 -1로 초기화
	table[0] = 0; // length* prices[0];

	for (int targetLength = 1; targetLength <= length; targetLength++)
	{
		int max_price = numeric_limits<int>::min();

		for (int cutLength = 1; cutLength <= targetLength; ++cutLength)
		{
			int price = 0;
			int cutLengthPrice = (cutLength == targetLength) ? prices[targetLength] : table[cutLength];
			int leftLength = targetLength;

			while (leftLength - cutLength >= 0)
			{
				leftLength -= cutLength;
				price += cutLengthPrice;
			}

			if (leftLength > 0)
			{
				price += table[leftLength];
			}

			max_price = std::max(max_price, price);
		}

		table[targetLength] = max_price;

		for (auto& t : table) cout << setw(3) << t; cout << endl;
	}

	return table[length];
}

// 어떻게 자르는지까지 출력하는 버전 (실행 예시 참고)
int ExtendedBottomUpCutRod(const vector<int>& prices, int length)
{
	vector<int> table(length + 1, -1); // 가격은 음수가 될 수 없으니까 디버깅 편의를 위해 -1로 초기화
	table[0] = 0; // length* prices[0];
	int finalSplitCnt = 0;
	int finalCutLength = 0;
	int finalLeftLength = 0;

	for (int targetLength = 1; targetLength <= length; targetLength++)
	{
		int max_price = numeric_limits<int>::min();

		for (int cutLength = 1; cutLength <= targetLength; ++cutLength)
		{
			int price = 0;
			int cutLengthPrice = (cutLength == targetLength) ? prices[targetLength] : table[cutLength];
			int leftLength = targetLength;
			int splitCnt = 0;

			while (leftLength - cutLength >= 0)
			{
				leftLength -= cutLength;
				price += cutLengthPrice;

				if (targetLength == length)
				{
					++splitCnt;
				}
			}

			if (leftLength > 0)
			{
				price += table[leftLength];
			}

			if (max_price < price)
			{
				max_price = price;

				if (targetLength == length)
				{
					finalSplitCnt = splitCnt;
					finalCutLength = cutLength;
					finalLeftLength = leftLength;
				}
			}
		}

		table[targetLength] = max_price;
	}

	std::cout << "Split: ";
	
	for (int splitCnt = 0; splitCnt < finalSplitCnt; ++splitCnt)
	{
		std::cout << finalCutLength << "(" << table[finalCutLength] << ") ";
	}

	if (finalLeftLength > 0)
	{
		std::cout << finalLeftLength << "(" << table[finalLeftLength] << ") ";
	}

	std::cout << std::endl;

	return table[length];
}

int main()
{
	// Length:                  0  1  2  3  4   5   6   7   8   9  10
	// vector<int> price_table = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	vector<int> price_table = { 0, 3, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	// 주의: price_table은 문제에서 주어진 조건입니다. 메모가 아닙니다.

	cout << "Naive recursion" << endl;
	for (int length = 0; length < price_table.size(); length++)
	{
		int revenue = RecurCutRod(price_table, length);
		cout << "Optimal revenue for length " << length << ": " << revenue << endl;
	}
	cout << endl;

	cout << "TopDown with Memoization" << endl;
	cout << "Optimal revenue for length " << 10 << ": " << MemoizedCutRod(price_table, 10) << endl;
	cout << endl;

	cout << "BottomUpTabulation" << endl;
	cout << "Optimal revenue for length " << 10 << ": " << BottomUpCutRod(price_table, 10) << endl;
	cout << endl;

	for (int length = 0; length < price_table.size(); length++)
	{
		cout << "Length: " << length << endl;
		int revenue = ExtendedBottomUpCutRod(price_table, length);
		cout << "Optimal revenue: " << revenue << endl;
	}

	return 0;
}
