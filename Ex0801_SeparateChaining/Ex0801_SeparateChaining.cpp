#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <list>
using namespace std;

// Sedgewick Ch3.1 p.375
template<typename T_KEY, typename T_VALUE>
class SequentialSearch
{
public:
	struct Node
	{
		T_KEY key;
		T_VALUE value;
	};

	Node* Find(T_KEY key)
	{
		// 찾았을 경우 주소 반환
		for (Node& node : m_chain)
		{
			if (node.key == key)
			{
				return &node;
			}
		}

		// 못 찾았을 경우 nullptr 반환
		// 찾았는지 못 찾았는 지에 대한 대응을 호출한 쪽으로 넘기는 방식
		// std::map, std::unordered_map에서는 iterator를 반환

		// cout << key << " was not found." << endl;

		return nullptr;
	}

	void Insert(Node n)
	{
		// 키를 찾아봤는데 없으면 추가
		if (Find(n.key) == nullptr)
		{
			m_chain.push_back(n);
		}

		// 이미 있을 경우에는 추가 X
	}

	void Reset()
	{
		m_chain.clear();
	}

	void Print()
	{
		for (auto& n : m_chain)
			cout << "(" << n.key << ", " << n.value << ")->";
		cout << endl;
	}

	int Size()
	{
		return int(m_chain.size());
	}

private:
	list<Node> m_chain;
};

template<typename T_KEY, typename T_VALUE>
class SeparateChaining
{
public:
	typedef typename SequentialSearch<T_KEY, T_VALUE>::Node Node;

	SeparateChaining(int c)
	{
		m_hashTable.resize(c);
		Reset();
	}

	Node* Find(T_KEY k)
	{
		const int hashVal = HashFunc(k);

		return m_hashTable[hashVal].Find(k);;
	}

	void Insert(Node n)
	{
		const int hashVal = HashFunc(n.key);

		m_hashTable[hashVal].Insert(n);
	}

	void Reset()
	{
		for (auto& s : m_hashTable)
			s.Reset();
	}

	void Print()
	{
		for (int i = 0; i < m_hashTable.size(); i++)
		{
			cout << i << ": ";
			m_hashTable[i].Print();
		}
	}

private:
	vector<SequentialSearch<T_KEY, T_VALUE>> m_hashTable;

	int HashFunc(int key)
	{
		return key % m_hashTable.size(); // 가장 간단한 해시 함수 사용
	}

	// int Hash(string key){ /* string을 hash값으로 변환 */ }
};

int main()
{
	// 난수 생성기
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int>  dist(1, 365);

	// 모인 인원 수
	int num_people = 23;

	// 이상적인 해시 크기는 365가 아니라 저장하고 싶은 데이터 수인 사람 수
	SeparateChaining<int, int> map(23); // 버킷 수를 늘리면 충돌 감소

	// 한 번만 테스트
	{
		int samebirthday_count = 0;

		for (int i = 0; i < num_people; i++)
		{
			int birthday = dist(g);

			auto* n = map.Find(birthday);

			if (n) // 이미 키(key)가 존재할 경우
			{
				samebirthday_count += 1;
				n->value += 1;
			}
			else
				map.Insert({ birthday, 1 }); // {생일, 이 날이 생일인 사람의 숫자}
		}

		map.Print();

		cout << samebirthday_count << endl;
	}

	// 아래는 반복 테스트
	int num_try = 10000;
	int all_samebirthday_count = 0;

	for (int t = 0; t < num_try; t++)
	{
		int samebirthday_count = 0;

		for (int i = 0; i < num_people; i++)
		{
			int birthday = dist(g);

			auto* n = map.Find(birthday);

			if (n) // 이미 키(key)가 존재할 경우
			{
				samebirthday_count += 1;
				n->value += 1;
			}
			else
				map.Insert({ birthday, 1 }); // {생일, 이 날이 생일인 사람의 숫자}
		}

		if (samebirthday_count > 0)
			all_samebirthday_count += 1;

		map.Reset(); // 다음 테스트를 위해 초기화
	}

	std::cout << (all_samebirthday_count * 100.0 / num_try) << " % " << endl;

	return 0;
}
