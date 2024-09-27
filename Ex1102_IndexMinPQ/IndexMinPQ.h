#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>

// https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/IndexMinPQ.java.html

template<typename Key>
class IndexMinPQ
{
public:
	IndexMinPQ(int cap)
	{
		m_capacity = cap;
		m_size = 0;
		m_keys.resize(m_capacity + 1);
		m_valueHeap.resize(m_capacity + 1); // heap[0]은 비워둡니다.
		m_valueIdxTable.resize(m_capacity + 1, -1); // -1로 초기화(아직 추가되지 않았다는 의미)
	}

	bool Empty()
	{
		return m_size == 0;
	}

	bool Contains(int i)
	{
		assert(i >= 0 && i < m_capacity);
		return m_valueIdxTable[i] != -1;
	}

	int Size() { return m_size; }

	void Insert(int value, Key key)
	{
		assert(value >= 0 && value < m_capacity);
		assert(!Contains(value));

		m_size += 1;
		m_valueIdxTable[value] = m_size;
		m_valueHeap[m_size] = value;
		m_keys[value] = key;
		Swim(m_size); // pq[size]를 자기 위치로 올려보냄

		// 정점의 개수가 고정되어 있다고 가정하면 resize 구현 불필요
	}

	int MinIndex()
	{
		return m_valueHeap[1]; // 1번 인덱스 자리
	}

	Key MinKey()
	{
		assert(m_size > 0);
		return m_keys[m_valueHeap[1]];

	}

	int DelMin()
	{
		assert(m_size != 0);

		int minValue = m_valueHeap[1];
		Exch(1, m_size--);
		Sink(1);

		assert(minValue == m_valueHeap[m_size + 1]);

		m_valueIdxTable[minValue] = -1; // 삭제했다는 의미
		m_keys[minValue] = 0.0; // 삭제했다는 의미, 디버깅용
		m_valueHeap[m_size + 1] = -1; // 삭제했다는 의미, 디버깅용

		return minValue;
	}

	Key keyOf(int i)
	{
		assert(i >= 0 && i < m_capacity);
		assert(Contains(i));

		return m_keys[i];
	}

	void ChangeKey(int i, Key key)
	{
		assert(i >= 0 && i < m_capacity);
		assert(Contains(i));

		m_keys[i] = key;
		Swim(m_valueIdxTable[i]);
		Sink(m_valueIdxTable[i]);
	}

	void DecreaseKey(int i, Key key)
	{
		assert(i >= 0 && i < m_capacity);
		assert(Contains(i));
		assert(key < m_keys[i]); // 새로운 키가 더 작아야 함

		m_keys[i] = key;
		Swim(m_valueIdxTable[i]);
	}

	void IncreaseKey(int i, Key key)
	{
		assert(i >= 0 && i < m_capacity);
		assert(Contains(i));
		assert(key > m_keys[i]); // 새로운 키가 더 작아야 함

		m_keys[i] = key;
		Sink(m_valueIdxTable[i]);
	}

	void Delete(int i)
	{
		assert(i >= 0 && i < m_capacity);
		assert(Contains(i));

		int index = m_valueIdxTable[i];
		Exch(index, m_size--);
		Swim(index);
		Sink(index);
		m_keys[i] = 0.0; // 삭제됐다는 의미, 디버깅용
		m_valueIdxTable[i] = -1; // 삭제됐다는 의미
	}

	void Exch(int i, int j)
	{
		int swap = m_valueHeap[i];
		m_valueHeap[i] = m_valueHeap[j];
		m_valueHeap[j] = swap;
		m_valueIdxTable[m_valueHeap[i]] = i;
		m_valueIdxTable[m_valueHeap[j]] = j;
	}

	bool Greater(int i, int j)
	{
		return m_keys[m_valueHeap[i]] > m_keys[m_valueHeap[j]];
	}

	void Swim(int targetIdx)
	{
		// TODO: 우선순위가 높은 것을 수영해서 수면위로 올라가듯 위로 올리는 과정
		// 힌트: Greater(), Exch() 사용

		int parentIdx = targetIdx / 2;

		while ((1 < targetIdx) && 
			   Greater(parentIdx, targetIdx))
		{
			Exch(parentIdx, targetIdx);
			targetIdx = parentIdx;
			parentIdx /= 2;
		}
	}

	void Sink(int targetIdx)
	{
		// TODO: 우선순위가 낮은 것을 밑으로 가라앉히는 과정
		// 힌트: Greater(), Exch() 사용
		
		while (targetIdx * 2 <= m_size)
		{
			int minIdx = targetIdx;
			const int leftIdx = targetIdx * 2;
			const int rightIdx = targetIdx * 2 + 1;

			// 왼쪽 자식과 비교
			if (Greater(minIdx, leftIdx))
			{
				minIdx = leftIdx;
			}

			// 오른쪽 자식과 비교
			if ((rightIdx <= m_size) &&
				Greater(minIdx, rightIdx))
			{
				minIdx = rightIdx;
			}

			// target이 최소면 루프 종료
			if (minIdx == targetIdx)
			{
				break;
			}

			// target의 value와 target보다 작은 자식의 value를 교환
			Exch(targetIdx, minIdx);
			targetIdx = minIdx;
		}
	}

	void Print()
	{
		using namespace std;
		cout << "Index: ";
		for (int i = 1; i <= m_size; i++)
			cout << setw(5) << i;
		cout << endl;

		cout << "Key:   ";
		for (int i = 1; i <= m_size; i++)
			cout << setw(5) << keyOf(m_valueHeap[i]);
		cout << endl;

		cout << "Value: ";
		for (int i = 1; i <= m_size; i++)
			cout << setw(5) << m_valueHeap[i];
		cout << endl << endl;
	}

private:
	int					m_size = 0;
	int					m_capacity = 0;
	std::vector<int>	m_valueHeap;		// key에 대응되는 value들의 힙
	std::vector<int>	m_valueIdxTable;	// m_valueHeap[m_valueIdxTable[value]] = value
	std::vector<Key>	m_keys;				// m_keys[value] = key
};

