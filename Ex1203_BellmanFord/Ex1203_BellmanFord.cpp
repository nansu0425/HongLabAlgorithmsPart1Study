#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

void Print(vector<double>& dist)
{
	for (int i = 0; i < dist.size(); i++)
		cout << setw(6) << dist[i];
	cout << endl;
}

void PrintPathHelper(vector<int>& prevTable, int dest)
{
	if (dest == -1)
	{
		return;
	}

	PrintPathHelper(prevTable, prevTable[dest]);

	std::cout << dest << " ";
}

void PrintPaths(vector<int>& prevTable)
{
	for (int dest = 0; dest < prevTable.size(); dest++)
	{
		PrintPathHelper(prevTable, dest);
		cout << endl;
	}
}

struct Edge
{
	int v, w; // v->w
	double weight;
};

int main()
{
	constexpr double infDist = numeric_limits<double>::infinity();

	// CLRS p.621 (다익스트라 예제와 같음)
	//vector<Edge> edges = {
	//{0, 1, 10.0},
	//{0, 3, 5.0},
	//{1, 2, 1.0},
	//{1, 3, 2.0},
	//{2, 4, 4.0},
	//{3, 1, 3.0},
	//{3, 2, 9.0},
	//{3, 4, 2.0},
	//{4, 0, 7.0},
	//{4, 2, 6.0},
	//};
	//int numVertices = 5; // number of vertices

	// 간선이 왼쪽에서 오른쪽 방향일 경우
	vector<Edge> edges = {
	{0, 1, 1.0}, // A->B 1
	{1, 2, 5.0},
	{1, 3, 4.0},
	{2, 3, -3.0},
	{3, 4, 1.0},
	{4, 3, -100.0} // 음의 싸이클이 추가된 경우
	};
	int numVertices = 5; // number of vertices

	//std::reverse(edges.begin(), edges.end()); // 간선 순서 뒤집어서 해보기

	// 간선 순서는 CLRS p613 예시 순서
	//vector<Edge> edges = {
	//	{1, 2, 5.0},
	//	{1, 3, 8.0},
	//	{1, 4, -4.0},
	//	{2, 1, -2.0},
	//	{3, 2, -3.0},
	//	{3, 4, 9.0},
	//	{4, 2, 7.0},
	//	{4, 0, 2.0},
	//	{0, 1, 6.0},
	//	{0, 3, 7.0},
	//};
	//int numVertices = 5; // number of vertices

	int numEdges = int(edges.size()); // number of edges

	vector<double> distTable(numVertices, infDist);
	vector<int> prevTable(numVertices, -1);

	int src = 0; // 시작 정점의 인덱스
	distTable[src] = 0.0;

	Print(distTable);

	for (int updateCount = 1; updateCount < numVertices; updateCount++)
	{
		for (const auto& edge : edges)
		{
			const double newDist = distTable[edge.v] + edge.weight;
			
			if (newDist < distTable[edge.w])
			{
				distTable[edge.w] = newDist;
				prevTable[edge.w] = edge.v;
			}
		}

		Print(distTable);
	}

	// 참고: infinity() 비교 연산
	// cout << bool(numeric_limits<double>::infinity() + 100 > numeric_limits<double>::infinity()) << endl;  // 0 false
	// cout << bool(numeric_limits<double>::infinity() + 100 < numeric_limits<double>::infinity()) << endl;  // 0 false
	// cout << bool(numeric_limits<double>::infinity() + 100 == numeric_limits<double>::infinity()) << endl; // 1 true
	// https://en.wikipedia.org/wiki/IEEE_754 부동소수점 표준에 따르면 수학적 정의와 동일하게 무한대 더하기 무한대는 무한대입니다. 

	for (const auto& edge : edges)
	{
		if (distTable[edge.v] + edge.weight < distTable[edge.w])
		{
			cout << "Negative cycle was found." << endl;
			return -1;
		}
	}

	cout << "Negative cycle was not found." << endl;

	PrintPaths(prevTable);

	return 0;
}