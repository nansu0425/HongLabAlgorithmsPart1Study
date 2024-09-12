#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric> // std::iota

using namespace std;

void Print(vector<int>& arr, int lo, int hi)
{
	// setfill(), setw()는 줄맞춤에 사용

	for (int i = 0; i < lo; i++)
		cout << "   ";
	for (int i = lo; i <= hi; i++)
		cout << setfill(' ') << setw(3) << arr[i];
	cout << endl;
}

bool CheckSorted(vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

// Sedgewick p. 278
class BottomupMerge
{
public:
	void Sort(vector<int>& target)
	{
		aux.resize(target.size());

		int N = static_cast<int>(target.size());

		// 병합 범위
		int range = 1;

		while (range < N)
		{
			// 병합 범위 2배씩 증가
			range <<= 1;

			for (int startIdx = 0; startIdx < N - range / 2; startIdx += range)
			{
				const int lowIdx = startIdx;
				const int midIdx = lowIdx + range / 2 - 1;
				const int highIdx = std::min(lowIdx + range - 1, N - 1);

				Merge(target, lowIdx, midIdx, highIdx);
			}
		}
	}

private:
	void Merge(vector<int>& target, int lo, int mid, int hi)
	{
		cout << "Before: ";
		Print(target, lo, hi);

		int auxLeftIdx = lo;
		int auxRightIdx = mid + 1;
		int targetIdx = lo;

		// 병합 범위의 원소가 정렬돼 있는 경우
		if (target[auxRightIdx - 1] <= target[auxRightIdx])
		{
			return;
		}

		std::copy(target.begin() + lo, target.begin() + hi + 1, aux.begin() + lo);

		// aux 원소를 크기 순으로 target에 복사
		while ((auxLeftIdx <= mid) && (auxRightIdx <= hi))
		{
			// auxLeftIdx의 원소가 더 작거나 같을 때
			if (aux[auxLeftIdx] <= aux[auxRightIdx])
			{
				target[targetIdx] = aux[auxLeftIdx];
				++auxLeftIdx;
			}
			// auxRightIdx의 원소가 더 작을 때
			else
			{
				target[targetIdx] = aux[auxRightIdx];
				++auxRightIdx;
			}

			++targetIdx;
		}
		
		// 복사하지 않은 나머지 aux 원소를 target으로 복사
		if (auxLeftIdx <= mid)
		{
			std::copy(aux.begin() + auxLeftIdx, aux.begin() + mid + 1, target.begin() + targetIdx);
		}
		else
		{
			std::copy(aux.begin() + auxRightIdx, aux.begin() + hi + 1, target.begin() + targetIdx);
		}

		cout << "After : ";
		Print(target, lo, hi);
	}

	vector<int> aux; // 추가 메모리
};

int main()
{
	vector<int> my_vector(19);
	std::iota(my_vector.begin(), my_vector.end(), 0);
	std::reverse(my_vector.begin(), my_vector.end());

	cout << "        ";
	Print(my_vector, 0, static_cast<int>(my_vector.size()) - 1);

	BottomupMerge merge;
	merge.Sort(my_vector);

	cout << "        ";
	Print(my_vector, 0, static_cast<int>(my_vector.size()) - 1);
}
