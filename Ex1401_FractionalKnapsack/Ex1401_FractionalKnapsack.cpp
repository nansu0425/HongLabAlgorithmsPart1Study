#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item
{
	double value;
	double weight;
};

void Print(vector<Item>& items)
{
	for (auto i : items)
	{
		// (가성비 = value/weight = ratio, value, weight)
		cout << "(" << i.value / i.weight << ", " << i.value << ", " << i.weight << ") ";
	}
	cout << endl;
}

bool Compare(struct Item a, struct Item b)
{
	double ratio_a = a.value / a.weight;
	double ratio_b = b.value / b.weight;

	return ratio_a > ratio_b; // ratio가 큰 쪽이 앞으로 오도록 정렬
}

double FractionalKnapsack(vector<Item> items, double limitWeight)
{
	sort(items.begin(), items.end(), Compare); // Compare() 함수를 이용해서 정렬

	cout << "limitWeight = " << limitWeight << endl;
	Print(items);

	double totalValue = 0.0;

	for (auto& item : items)
	{
		const double weight = min(limitWeight, item.weight);

		totalValue += item.value / item.weight * weight;
		item.weight -= weight;
		limitWeight -= weight;

		cout << "limitWeight = " << limitWeight << endl;
		Print(items);

		if (limitWeight == 0)
		{
			break;
		}
	}

	return totalValue;
}

int main()
{
	double limitWeight = 6.0;

	vector<Item> items = { { 10, 1 }, { 28, 4 }, { 12, 2 }, { 12, 3 } };

	cout << FractionalKnapsack(items, limitWeight) << endl;

	return 0;
}
