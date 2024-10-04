#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std; // 편의용

class UnionFind
{
public:
	vector<int> m_groupTable;
	int m_numGroups;

	UnionFind(int numGroups)
		: m_groupTable(numGroups)
		, m_numGroups(numGroups)
	{
		for (int elem = 0; elem < m_groupTable.size(); elem++)
		{
			m_groupTable[elem] = elem;
		}
	}

	int NumGroups()
	{
		return m_numGroups;
	}

	bool Connected(int p, int q)
	{
		return Find(p) == Find(q);
	}

	/* Quick-Find 방식: Union()에서 미리 정리하기 때문에 Find()는 빠름 */
	/*int Find(int p)
	{
		return m_groupTable[p];
	}

	void Union(int first, int second)
	{
		int groupFirst = Find(first);
		int groupSecond = Find(second);

		if (groupFirst == groupSecond) 
		{
			return;
		}

		for (int elem = 0; elem < m_groupTable.size(); elem++)
		{
			if (m_groupTable[elem] == groupFirst)
			{
				m_groupTable[elem] = groupSecond;
			}
		}

		m_numGroups--;
	}*/

	/* Quick-Union 방식: Union()은 빠르고 Find()할 때 정리 */
	
	int Find(int elem)
	{
		while (elem != m_groupTable[elem])
		{
			elem = m_groupTable[elem];
		}

		return elem;
	}

	void Union(int firstElem, int secondElem)
	{
		int groupFirst = Find(firstElem);
		int groupSecond = Find(secondElem);

		if (groupFirst == groupSecond) 
		{
			return;
		}

		m_groupTable[groupFirst] = groupSecond;
		m_numGroups--;
	}
	

	void Print()
	{
		cout << "Num groups = " << NumGroups() << endl;

		cout << "Index:";
		for (int i = 0; i < m_groupTable.size(); i++)
			cout << setw(3) << i;
		cout << endl;

		cout << "Group:";
		for (auto i : m_groupTable)
			cout << setw(3) << i;
		cout << endl;
	}
};
