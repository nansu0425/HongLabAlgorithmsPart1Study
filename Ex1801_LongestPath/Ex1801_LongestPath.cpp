#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Vertex
{
	int					value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool				isVisited = false;
	vector<Vertex*>		ptrsOutNeighbor; // 나가는 방향의 이웃 vertex들에 대한 포인터

	Vertex(int val)
		: value(val)
	{}
};

class Graph
{
public:
	Graph(int numVertices)
	{
		m_ptrVertexTable.resize(numVertices);

		for (int key = 0; key < numVertices; key++)
		{
			m_ptrVertexTable[key] = new Vertex(key);
		}
	}

	~Graph()
	{
		for (auto* ptrVertex : m_ptrVertexTable)
		{
			delete ptrVertex;
		}
	}

	void AddDiEdge(int key, int outNeighborKey) // 단방향 간선
	{
		m_ptrVertexTable[key]->ptrsOutNeighbor.push_back(m_ptrVertexTable[outNeighborKey]);
	}

	void AddBiEdge(int key, int neighborKey) // 양방향 간선
	{
		AddDiEdge(key, neighborKey);
		AddDiEdge(neighborKey, key);
	}

	void DFS(int source)
	{
		cout << "Depth-first Search: ";
		for (auto* v : this->m_ptrVertexTable)
			v->isVisited = false;
		DFS(m_ptrVertexTable[source]);
		cout << endl;
	}

	void DFS(Vertex* source)
	{
		cout << source->value << " ";
		source->isVisited = true;
		for (auto* w : source->ptrsOutNeighbor)
			if (!w->isVisited)
				DFS(w);
	}

	void DepthFirstPath(int sourceKey, int sinkKey)
	{
		cout << "Paths from " << m_ptrVertexTable[sourceKey]->value << " to " << m_ptrVertexTable[sinkKey]->value << endl;

		m_longestPath.clear();

		for (auto* ptrVertex : m_ptrVertexTable)
		{
			ptrVertex->isVisited = false;
		}

		vector<Vertex*> path;
		path.reserve(m_ptrVertexTable.size());

		DepthFirstPathHelper(m_ptrVertexTable[sourceKey], m_ptrVertexTable[sinkKey], path);

		cout << "Longest length : " << int(m_longestPath.size() - 1) << endl;
		cout << "Longest path : ";
		PrintPath(m_longestPath);
	}

private:
	vector<Vertex*> m_ptrVertexTable; // key to pointer to vertex
	vector<Vertex*> m_longestPath;

	void DepthFirstPathHelper(Vertex* ptrSource, Vertex* ptrSink, vector<Vertex*>& path)
	{
		path.push_back(ptrSource);

		// 목적지에 도달한 경우
		if (ptrSource == ptrSink)
		{
			cout << "Found: ";
			PrintPath(path);

			// path가 현재 가장 긴 경로인 경우
			if (m_longestPath.size() < path.size())
			{
				m_longestPath = path;
			}

			path.pop_back();

			return;
		}

		// 방문 처리, 경로 기록
		ptrSource->isVisited = true;

		PrintPath(path);

		// 이웃 정점 탐색
		for (Vertex* ptrOutNeighbor : ptrSource->ptrsOutNeighbor)
		{
			// 방문한 정점이면 다른 이웃 탐색
			if (ptrOutNeighbor->isVisited == true)
			{
				continue;
			}

			DepthFirstPathHelper(ptrOutNeighbor, ptrSink, path);
		}

		// 방문 기록 및 경로 제거
		ptrSource->isVisited = false;
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
	Graph g(6);

	// 주의: 양방향 간선 (undirected graph)
	g.AddBiEdge(0, 2);
	g.AddBiEdge(2, 1);
	g.AddBiEdge(2, 3);
	g.AddBiEdge(3, 4);
	g.AddBiEdge(1, 5);
	g.AddBiEdge(2, 4);
	g.AddBiEdge(3, 5);

	g.DepthFirstPath(0, 4);

	return 0;
}

