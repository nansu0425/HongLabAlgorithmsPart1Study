#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;

	bool visited = false;

	vector<Vertex*> out_neighbors;
	vector<Vertex*> in_neighbors; // Transpose 쉽게 하려고 저장
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

	void AddDiEdge(int v, int w)
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->in_neighbors.push_back(vertices[v]);
	}

	deque<Vertex*> ReversePostorderDFS()
	{
		revpost = deque<Vertex*>();

		for (auto* v : this->vertices)
			v->visited = false;

		for (auto* v : this->vertices)
			if (!v->visited)
				ReversePostorderDFS(v);

		return revpost;
	}

	void Transpose()
	{
		// 인접 행렬 표현에서 행렬을 transpose 시키는 것과 동일
		for (Vertex* pVertex : vertices)
		{
			std::swap(pVertex->in_neighbors, pVertex->out_neighbors);
		}
	}

	void KosarajuStrongComponents()
	{
		// 그래프의 모든 간선 방향을 반대로 바꾼다
		// Transpose(); // 생략하면 출력 순서는 달라지만 결과는 동일

		// 방문 기록 초기화
		for (Vertex* pVertex : vertices)
		{
			pVertex->visited = false;
		}

		// reverse postorder 탐색 기록을 revpost에 저장
		for (Vertex* pSrc : vertices)
		{
			if (pSrc->visited == false)
			{
				ReversePostorderDFS(pSrc);
			}
		}

		cout << "Reverse Post-order: ";

		for (auto* v : revpost)
		{
			cout << v->value << " ";
		}

		cout << endl;

		// 원본 그래프로 돌아온다
		Transpose();

		// SCC id 정보 초기화
		componentIds.resize(revpost.size(), -1);

		// 방문 기록 초기화
		for (Vertex* pVertex : vertices)
		{
			pVertex->visited = false;
		}

		// 각 SCC를 DFS로 분류
		for (Vertex* pVertex : revpost)
		{
			if (componentIds[pVertex->value] == -1)
			{
				DFS(pVertex);
				++componentCount;
			}
		}

		// 결과 정리 후 출력
		vector<vector<int>> components(componentCount);

		for (int s = 0; s < vertices.size(); s++)
			components[componentIds[s]].push_back(s);

		cout << componentCount << " strong components" << endl;

		for (int i = 0; i < components.size(); i++)
		{
			cout << "Kosaraju strong component " << i + 1 << ": ";
			for (auto v : components[i])
				cout << v << " ";
			cout << endl;
		}
	}

private:
	vector<Vertex*> vertices;
	deque<Vertex*> revpost; // for문 편의상 stack대신 deque 사용
	vector<int> componentIds;
	int componentCount = 0;

	// 	void TopologicalSortHelper(Vertex* v)
	void ReversePostorderDFS(Vertex* pSrc)
	{
		pSrc->visited = true;

		for (Vertex* pOutNeighbor : pSrc->out_neighbors)
		{
			if (pOutNeighbor->visited == false)
			{
				ReversePostorderDFS(pOutNeighbor);
			}
		}

		revpost.push_front(pSrc);
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

	// ReversePostorderDFS()도 깊이우선탐색이라서 DSF()와 합칠 수 있으나
	// 여기서는 디버깅 편의를 위해 분리하였습니다.
};

int main()
{
	// Sedgewick p569
	// 방향(directed) 그래프
	vector<vector<int>> edges = {
		{4, 2}, {2, 3}, {3, 2}, {6, 0}, {0, 1},	{2, 0}, {11, 12}, {12, 9}, {9, 10},
		{9, 11}, {7, 9}, {10, 12}, {11, 4}, {4, 3}, {3, 5}, {6, 8}, {8, 6}, {5, 4},
		{0, 5}, {6, 4},	{6, 9}, {7, 6} };
	Graph g(13);

	for (vector<int>& p : edges)
		g.AddDiEdge(p[0], p[1]);

	g.KosarajuStrongComponents();

	return 0;
}
