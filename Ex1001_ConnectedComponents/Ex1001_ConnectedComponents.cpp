﻿
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Vertex*> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
};

class Graph
{
public:
	Graph(int num_vertices)
	{
		vertices.resize(num_vertices);
		for (int i = 0; i < num_vertices; i++)
			vertices[i] = new Vertex(i);
	}

	~Graph()
	{
		for (auto* v : vertices)
			delete v;
	}

	//void AddDiEdge(int v, int w) // 단방향 간선
	//{
	//	vertices[v]->out_neighbors.push_back(vertices[w]);
	//}

	void AddBiEdge(int v, int w) // 양방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->out_neighbors.push_back(vertices[v]);
	}

	void DFS(Vertex* pSrc)
	{
		pSrc->visited = true;
		componentIds[pSrc->value] = componentCount;

		for (Vertex* pOutNeighbor : pSrc->out_neighbors)
		{
			if (pOutNeighbor->visited == false)
			{
				DFS(pOutNeighbor);
			}
		}
	}

	void ConnectedComponents()
	{
		componentCount = 0;
		componentIds.resize(vertices.size(), -1);

		for (Vertex* pVertex : vertices)
		{
			pVertex->visited = false;
		}

		for (Vertex* pSrc : vertices)
		{
			if (pSrc->visited == false)
			{
				DFS(pSrc);
				++componentCount;
			}
		}

		// 결과 정리 후 출력
		vector<vector<int>> components(componentCount);

		for (int vertexId = 0; vertexId < vertices.size(); vertexId++)
		{
			components[componentIds[vertexId]].push_back(vertexId);
		}

		cout << componentCount << " components" << endl;

		for (int i = 0; i < components.size(); i++)
		{
			cout << "Component " << i + 1 << ": ";
			for (auto v : components[i])
				cout << v << " ";
			cout << endl;
		}
	}

private:
	vector<Vertex*> vertices;
	vector<int> componentIds;
	int componentCount = 0;
};


int main()
{
	// Sedgewick p544
	// 무방향(양방향) 그래프
	vector<vector<int>> edges = { {0, 5}, {4, 3}, {0, 1},
		{9, 12}, {6, 4}, {5, 4}, {0, 2}, {11, 12}, {9, 10},
		{0, 6}, {7, 8}, {9, 11}, {5, 3} };

	Graph g(13);

	for (vector<int>& p : edges)
		g.AddBiEdge(p[0], p[1]);

	g.ConnectedComponents();

	return 0;
}
