#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <iostream>

using namespace std;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}

int Count1(const vector<int>& arr, int x)
{
	int count = 0;

	for (int i : arr)
	{
		if (i == x)
		{
			++count;
		}
	}

	return count;
}

int Count2(const vector<int>& arr, int x)
{
	int leftIdx = 0;
	int rightIdx = arr.size() - 1;
	int midIdx = 0;
	int count = 0;

	while (leftIdx <= rightIdx)
	{
		midIdx = leftIdx + (rightIdx - leftIdx) / 2;

		if (arr[midIdx] < x)
		{
			leftIdx = midIdx + 1;
		}
		else if (x < arr[midIdx])
		{
			rightIdx = midIdx - 1;
		}
		else
		{
			++count;
			break;
		}
	}

	leftIdx = midIdx - 1;
	rightIdx = midIdx + 1;

	while ((-1 < leftIdx) && (arr[leftIdx] == x))
	{
		++count;
		--leftIdx;
	}

	while ((rightIdx < arr.size()) && (arr[rightIdx] == x))
	{
		++count;
		++rightIdx;
	}

	return count;
}

int Count3(const vector<int>& arr, int x)
{
	int leftIdx = 0;
	int rightIdx = arr.size() - 1;
	int midIdx = 0;

	while (leftIdx <= rightIdx)
	{
		midIdx = leftIdx + (rightIdx - leftIdx) / 2;

		if (arr[midIdx] < x)
		{
			leftIdx = midIdx + 1;
		}
		else if (x < arr[midIdx])
		{
			rightIdx = midIdx - 1;
		}
		else
		{
			break;
		}
	}

	if (rightIdx < leftIdx)
	{
		return 0;
	}

	int lowestIdx = 0;
	int lowLeftIdx = leftIdx;
	int lowRightIdx = rightIdx;

	while (lowLeftIdx <= lowRightIdx)
	{
		lowestIdx = lowLeftIdx + (lowRightIdx - lowLeftIdx) / 2;

		if (arr[lowestIdx] < x)
		{
			lowLeftIdx = lowestIdx + 1;
		}
		else if (x < arr[lowestIdx])
		{
			lowRightIdx = lowestIdx - 1;
		}
		else
		{
			if ((lowestIdx == 0) || (arr[lowestIdx - 1] != x))
			{
				break;
			}

			lowRightIdx = lowestIdx - 1;
		}
	}

	int highestIdx = 0;
	int highLeftIdx = leftIdx;
	int highRightIdx = rightIdx;

	while (highLeftIdx <= highRightIdx)
	{
		highestIdx = highLeftIdx + (highRightIdx - highLeftIdx) / 2;

		if (arr[highestIdx] < x)
		{
			highLeftIdx = highestIdx + 1;
		}
		else if (x < arr[highestIdx])
		{
			highRightIdx = highestIdx - 1;
		}
		else
		{
			if ((highestIdx == arr.size() - 1) || (arr[highestIdx + 1] != x))
			{
				break;
			}

			highLeftIdx = highestIdx + 1;
		}
	}

	return highestIdx - lowestIdx + 1;
}

int main()
{
	random_device rd;
	mt19937 gen(rd());

	const int n = 20;
	vector<int> my_vector(n);

	int x = 6; // target to find

	for (int r = 0; r < 100; r++)
	{
		uniform_int_distribution<int> value_distribution(1, 10);
		generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
		sort(my_vector.begin(), my_vector.end());

		Print(my_vector);

		const int expected_count = std::count(my_vector.begin(), my_vector.end(), x);

		cout << "Expected count = " << expected_count << endl;

		// 1. O(n) brute force
		if (Count1(my_vector, x) != expected_count)
		{
			cout << "Wrong count1: " << Count1(my_vector, x) << endl;
			exit(-1);
		}

		// 2. O(log(n) + count)
		if (Count2(my_vector, x) != expected_count)
		{
			cout << "Wrong count2: " << Count2(my_vector, x) << endl;
			exit(-1);
		}

		// 3. O(log(n))
		if (Count3(my_vector, x) != expected_count)
		{
			cout << "Wrong count3: " << Count3(my_vector, x) << endl;
			exit(-1);
		}
	}

	cout << "Good!" << endl;

	return 0;
}
