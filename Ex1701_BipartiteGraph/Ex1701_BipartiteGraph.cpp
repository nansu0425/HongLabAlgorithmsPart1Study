#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <iomanip>
using namespace std;

void Print(vector<int>& colors)
{
	for (auto c : colors)
		cout << std::setw(3) << c;
	cout << endl;
}

bool IsBipartite(const vector<vector<int>>& graph)
{
	int numVertices = int(graph.size());
	vector<int> colorTable(numVertices, -1);

	colorTable[0] = 0;

	queue<int> coloredVertices;
	coloredVertices.push(0);

	while (!coloredVertices.empty())
	{
		int visitedVertex = coloredVertices.front();
		coloredVertices.pop();

		assert(graph[visitedVertex][visitedVertex] == 0);

		for (int neighborVertex = 0; neighborVertex < numVertices; ++neighborVertex)
		{
			Print(colorTable);

			// 이웃 정점이 아니면 다음 정점으로 넘어간다
			if (graph[visitedVertex][neighborVertex] == 0)
			{
				continue;
			}

			if (colorTable[neighborVertex] == -1)
			{
				colorTable[neighborVertex] = 1 - colorTable[visitedVertex]; // color는 0 또는 1, 이웃은 다른 색으로 설정
				coloredVertices.push(neighborVertex);
			}
			else if (colorTable[visitedVertex] == colorTable[neighborVertex])
			{
				cout << visitedVertex << " " << neighborVertex << endl;
				return false;
			}
		}

		Print(colorTable);
	}

	return true;
}

int main()
{
	{
		vector<vector<int>> graph =
		{
			{0, 1, 1},
			{1, 0, 1},
			{1, 1, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	{
		vector<vector<int>> graph =
		{
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	{
		vector<vector<int>> graph =
		{
			{0, 1, 1, 1}, // <- 0-1 추가
			{1, 0, 1, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	return 0;
}

// 참고자료
// https://www.geeksforgeeks.org/bipartite-graph/