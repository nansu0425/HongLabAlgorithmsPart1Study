﻿#include <iostream>
#include <vector>
#include <limits>
#include "../Ex1102_IndexMinPQ/IndexMinPQ.h"
using namespace std;

constexpr double infDist = numeric_limits<double>::infinity();

struct DirectedEdge
{
	int u;         // 간선 시작(edge tail, 화살표 꼬리) 정점의 인덱스
	int v;         // 간선 끝(edge head, 화살촉) 정점의 인덱스
	double weight; // edge weight (여기서는 u-v 이동 비용)
};

class EdgeWeightedDigraph
{
public:
	vector<vector<DirectedEdge>> adj;

	EdgeWeightedDigraph(int num_vertices)
	{
		adj.resize(num_vertices);
	}

	void AddBiEdge(DirectedEdge e) // 양방향(무방향)
	{
		adj[e.u].push_back(e);
		adj[e.v].push_back({ e.v, e.u, e.weight });
	}

	vector<DirectedEdge>& Adj(int v)
	{
		return adj[v];
	}

	void PrimMST()
	{
		int numVertices = int(adj.size());

		vector<double> minWeightTable(numVertices, infDist);     // dist in Sedgewick Algorithm 4.7, key in CLRS p. 596
		vector<int> prevTable(numVertices);              // pi in CLRS

		double sumWeight = 0.0;

		minWeightTable[0] = 0.0;
		prevTable[0] = -1;

		IndexMinPQ<double> pq(numVertices);

		// TODO: 우선순위큐에다가 일단 모든 정점의 인덱스를 넣는다.
		//       위에서 key[0] = 0.0 이기 때문에 0번이 가장 위로 온다.
		for (int vertex = 0; vertex < numVertices; ++vertex)
		{
			pq.Insert(vertex, minWeightTable[vertex]);
		}

		while (!pq.Empty())
		{
			int u = pq.DelMin();

			if (prevTable[u] >= 0)
			{
				sumWeight += minWeightTable[u];
				cout << prevTable[u] << " - " << u << " : " << minWeightTable[u] << endl;
			}

			for (const DirectedEdge& e : Adj(u))
			{
				const int v = e.v;
				const double weight = e.weight; // u-v 간선 비용

				// TODO: v가 pq안에 아직 있는지 && u-v 비용이 더 적은지
				if (pq.Contains(v) && 
					(weight < pq.keyOf(v)))
				{
					prevTable[v] = u;
					minWeightTable[v] = weight;
					pq.ChangeKey(v, weight);
				}
			}
		}

		cout << sumWeight << endl;
	}
};

int main()
{
	vector<DirectedEdge> edges =
	{
		{ 0, 1, 4.0 },
		{ 0, 7, 9.0 },
		{ 1, 2, 8.0 },
		{ 1, 7, 11.0 },
		{ 2, 3, 7.0 },
		{ 2, 5, 4.0 },
		{ 2, 8, 2.0 },
		{ 3, 4, 9.0 },
		{ 3, 5, 14.0 },
		{ 4, 5, 10.0 },
		{ 5, 6, 2.0 },
		{ 6, 7, 1.0 },
		{ 6, 8, 6.0 },
		{ 7, 8, 7.0 },
	};

	EdgeWeightedDigraph g(9);

	for (auto e : edges)
	{
		g.AddBiEdge(e);
	}

	g.PrimMST();

	return 0;
}
