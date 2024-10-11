#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Edge
{
	int from = 0;
	int to = 0;
	int weight = 0;
};

struct Vertex
{
	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool isVisited = false;
	vector<Edge> outNeighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터

	Vertex(int val)
		: value(val)
	{}
};

class Graph
{
public:
	Graph(int numVertices)
	{
		m_vertexTable.resize(numVertices);

		for (int key = 0; key < numVertices; key++)
		{
			m_vertexTable[key] = new Vertex(key);
		}
	}

	~Graph()
	{
		for (Vertex* pVertex : m_vertexTable)
		{
			delete pVertex;
		}
	}

	void AddDiEdge(int key, int outNeighborKey, int weight) // 단방향 간선
	{
		m_vertexTable[key]->outNeighbors.push_back(Edge{ key, outNeighborKey, weight });
	}

	void AddBiEdge(int key, int neighborKey, int weight) // 양방향 간선
	{
		AddDiEdge(key, neighborKey, weight);
		AddDiEdge(neighborKey, key, weight);
	}

	void TravellingSalesman(int sourceKey)
	{
		cout << "Start : " << m_vertexTable[sourceKey]->value << endl;

		m_minCostPath.clear();

		for (Vertex* pVertex : m_vertexTable)
		{
			pVertex->isVisited = false;
		}

		vector<Vertex*> path;
		path.reserve(m_vertexTable.size());

		TravellingSalesmanHelper(m_vertexTable[sourceKey], m_vertexTable[sourceKey], path, 0);

		cout << "Minimum cost : " << m_minCost << endl;
		cout << "Minimum path : ";
		PrintPath(m_minCostPath);
	}

private:
	vector<Vertex*>		m_vertexTable;
	vector<Vertex*>		m_minCostPath;
	int					m_minCost = numeric_limits<int>::max(); // large number

	void TravellingSalesmanHelper(Vertex* pSource, Vertex* pSink, vector<Vertex*>& path, int cost)
	{
		// 경로 기록
		path.push_back(pSource);

		// 시작 정점으로 돌아온 경우
		if ((path.size() > 1) && 
			(pSource == pSink))
		{
			// 모든 정점을 방문하지 않은 경우 (해밀턴 순회가 아닌 경우)
			if (path.size() <= m_vertexTable.size())
			{
				cout << "Discard: ";
				PrintPath(path);
			}
			else
			{
				cout << "Found: ";
				PrintPath(path);
				cout << cost << endl;

				// cost가 최소인 경우
				if (cost < m_minCost)
				{
					m_minCost = cost;
					m_minCostPath = path;
				}
			}

			path.pop_back();

			return;
		}

		// 시작점이 아니면 방문 처리
		if (pSource != pSink)
		{
			pSource->isVisited = true;
		}

		// 이웃 정점 탐색
		for (Edge& outNeighbor : pSource->outNeighbors)
		{
			// 이미 방문한 정점이면 다른 정점 탐색
			if (m_vertexTable[outNeighbor.to]->isVisited == true)
			{
				continue;
			}

			TravellingSalesmanHelper(m_vertexTable[outNeighbor.to], 
									 pSink, 
									 path, 
									 cost + outNeighbor.weight);
		}

		// 다른 경로 탐색을 위한 방문, 경로 기록 삭제
		pSource->isVisited = false;
		path.pop_back();
	}

	void PrintPath(vector<Vertex*> path)
	{
		for (auto& v : path) {
			cout << v->value;
			if (&v != &path.back())
				cout << " -> ";
		}
		cout << endl;
	}
};

int main()
{
	Graph g(4);

	// 주의: 양방향 간선 (undirected graph)
	g.AddBiEdge(0, 1, 20);
	g.AddBiEdge(0, 2, 25);
	g.AddBiEdge(0, 3, 30);
	g.AddBiEdge(1, 2, 10);
	g.AddBiEdge(2, 3, 35);
	g.AddBiEdge(3, 1, 15);

	g.TravellingSalesman(0);

	return 0;
}

