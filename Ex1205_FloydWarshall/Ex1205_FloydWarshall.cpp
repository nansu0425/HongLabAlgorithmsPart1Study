﻿#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <deque>
using namespace std;

constexpr double infDist = numeric_limits<double>::infinity();

template<typename T>
void Print(const vector<vector<T>>& dist)
{
	size_t V = dist.size();

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			cout << setw(5) << dist[i][j];
		cout << endl;
	}
	cout << endl;
}

void Print(int i, int j, double w)
{
	cout << "(" << i << "," << j << "," << w << ")";
}

void PrintPaths(vector<int> prev)
{
	for (int i = 0; i < prev.size(); i++)
	{
		deque<int> path;
		path.push_front(i);
		int v = prev[i];
		while (v != -1)
		{
			path.push_front(v);
			v = prev[v];
		}

		for (auto v : path) {
			cout << v;
			if (v != path.back())
				cout << " -> ";
		}
		cout << endl;
	}
}

void RepeatingBellmanFord(const vector<vector<double>>& origDistTable)
{
	// 힌트: 벨먼-포드를 여러 번 반복하는 방식
	cout << "Repeating Bellman-Ford" << endl;

	vector<vector<double>> distTable = origDistTable; // 복사 후 업데이트 하는 방식

	size_t numVertices = origDistTable.size();
	vector<vector<int>> prevTable(numVertices, vector<int>(numVertices));

	for (int src = 0; src < numVertices; src++)
	{
		for (int dest = 0; dest < numVertices; dest++)
		{
			prevTable[src][dest] = ((src == dest) ||
									(origDistTable[src][dest] == infDist))
									? -1
									: src;
		}
	}

	cout << "dist 0" << endl;
	Print(distTable);
	cout << "prev 0" << endl;
	Print(prevTable);

	for (int src = 0; src < numVertices; src++) // s는 시작 정점
	{
		for (int updateCnt = 1; updateCnt < numVertices; updateCnt++)
		{
			// CLRS 교재에서는 Floyd-Warshall을 구현할 때 사본을 만들어서 업데이트 방식이라서
			// 여기서는 이해를 돕기 위해 Bellman-Ford도 비슷하게 구조를 바꿔봤습니다.
			// 참고로, 위키피디아에서는 사본 없이 바로 덮어쓰는 in-place 방식입니다.
			auto newDistTable = distTable;
			auto newPrevTable = prevTable;

			// Bellman-Ford에 인접 리스트 대신에 인접 행렬 사용
			for (int prevDest = 0; prevDest < numVertices; prevDest++)
			{
				for (int dest = 0; dest < numVertices; dest++)
				{
					const double newDist = distTable[src][prevDest] + origDistTable[prevDest][dest];

					if (newDist < distTable[src][dest])
					{
						newDistTable[src][dest] = newDist;
						newPrevTable[src][dest] = prevDest;
					}
				}
			}

			distTable = std::move(newDistTable);
			prevTable = std::move(newPrevTable);

			cout << "dist " << src + 1 << endl;
			Print(distTable);
			cout << "prev " << src + 1 << endl;
			Print(prevTable);

			cout << "Paths " << src + 1 << endl;
			for (int i = 0; i < prevTable.size(); i++) {
				cout << "From " << i << " to others:" << endl;
				PrintPaths(prevTable[i]);
			}
		}
	}
}

void FloydWarshall(const vector<vector<double>>& origDistTable)
{
	cout << "FloydWarshall" << endl;

	vector<vector<double>> distTable = origDistTable; // 복사 후 업데이트 하는 방식

	const size_t numVertices = origDistTable.size();
	vector<vector<int>> prevTable(numVertices, vector<int>(numVertices));

	for (int src = 0; src < numVertices; src++)
	{
		for (int dest = 0; dest < numVertices; dest++)
		{
			prevTable[src][dest] = ((src == dest) || 
									(origDistTable[src][dest] == infDist)) 
									? -1 
									: src;
		}
	}

	cout << "dist 0" << endl;
	Print(distTable);
	cout << "prev 0" << endl;
	Print(prevTable);

	for (int stopover = 0; stopover < numVertices; stopover++)
	{
		auto newDistTable = distTable;
		auto newPrevTable = prevTable;

		for (int src = 0; src < numVertices; src++)
		{
			for (int dest = 0; dest < numVertices; dest++)
			{
				const double newDist = distTable[src][stopover] + distTable[stopover][dest];

				if (newDist < distTable[src][dest])
				{
					newDistTable[src][dest] = newDist;
					newPrevTable[src][dest] = prevTable[stopover][dest];
				}
			}
		}

		distTable = std::move(newDistTable);
		prevTable = std::move(newPrevTable);

		cout << "dist " << stopover + 1 << endl;
		Print(distTable);
		cout << "prev " << stopover + 1 << endl;
		Print(prevTable);

		cout << "Paths " << stopover + 1 << endl;
		for (int i = 0; i < prevTable.size(); i++) {
			cout << "From " << i << " to others:" << endl;
			PrintPaths(prevTable[i]);
		}
	}
}

int main()
{
	vector<vector<double>> distTable =
	{
		{0.0, 3.0, 8.0, infDist, -4.0},
		{infDist, 0.0, infDist, 1.0, 7.0},
		{infDist, 4.0, 0.0, infDist, infDist},
		{2.0, infDist, -5.0, 0.0, infDist},
		{infDist, infDist, infDist, 6.0, 0.0}
	};

	// RepeatingBellmanFord(distTable);

	FloydWarshall(distTable);
}
