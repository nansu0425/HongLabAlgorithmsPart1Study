#include <limits.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <list>

using namespace std;

class FlowEdge
{
public:
	FlowEdge() = default;

	FlowEdge(int from, int to, double capacity)
		: m_from(from)
		, m_to(to)
		, m_capacity(capacity)
	{}

	FlowEdge(int from, int to, double capacity, double flow)
		: m_from(from)
		, m_to(to)
		, m_capacity(capacity)
		, m_flow(flow)
	{}

	int GetFrom() const { return m_from; }
	int GetTo() const { return m_to; }
	double GetCapacity() const { return m_capacity; }
	double GetFlow() const { return m_flow; }

	int GetOther(int vertex) const
	{
		if (vertex == m_from) return m_to;
		else if (vertex == m_to) return m_from;
		else {
			assert(false);
			return -1;
		}
	}

	double GetResidualCapacityTo(int vertex) const
	{
		if (vertex == m_from) return m_flow;
		else if (vertex == m_to) return m_capacity - m_flow;

		assert(false);

		return 0.0;
	}

	void UpdateFlowTo(int vertex, double delta)
	{
		if (vertex == m_from) m_flow -= delta;
		else if (vertex == m_to) m_flow += delta;
		else assert(false);
	}

	void Print() const
	{
		cout << m_from << "->" << m_to << " " << m_flow << "/" << m_capacity << endl;
	}

private:
	int		m_from = -1;
	int		m_to = -1;
	double	m_capacity = 0.0; // 최대 용량
	double	m_flow = 0.0;     // 현재 유량
};

class FlowNetwork
{
public:
	FlowNetwork(int numVertices)
		: m_numVertices(numVertices)
		, m_numEdges(0)
		, m_edgesTable(numVertices)
	{}

	void AddEdge(const FlowEdge& e)
	{
		FlowEdge* pNewEdge = new FlowEdge(e);
		int from = e.GetFrom();
		int to = e.GetOther(from);

		m_edgesTable[from].push_back(pNewEdge); // edge of out_neighbor
		m_edgesTable[to].push_back(pNewEdge); // edge of in_neighbor
	}

	int GetNumVertices() const { return m_numVertices; }

	const list<FlowEdge*>& GetEdges(int vertex) const
	{
		return m_edgesTable[vertex];
	}

	vector<FlowEdge*> GetAllEdges() 
	{
		vector<FlowEdge*> allEdges;
		allEdges.reserve(m_numEdges / 2);

		for (int vertex = 0; vertex < m_numVertices; vertex++)
		{
			for (const auto& edge : GetEdges(vertex))
			{
				// 이미 추가한 edge인지 검사하여 중복 추가 방지
				if (edge->GetOther(vertex) > vertex)
				{
					allEdges.push_back(edge);
				}
			}
		}
		return allEdges;
	}

private:
	int						m_numVertices = 0;
	int						m_numEdges = 0;
	vector<list<FlowEdge*>> m_edgesTable;
};

class FordFulkerson
{
public:
	FordFulkerson(FlowNetwork& flowNet, int source, int sink)
		: m_scheduledTable(flowNet.GetNumVertices())
		, m_prevTable(flowNet.GetNumVertices())
	{
		while (IsAugmentingPath(flowNet, source, sink) == true)
		{
			// 힌트: Other(), ResidualCapacityTo(), UpdateFlowTo() 사용
			double minResidualCapacity = std::numeric_limits<double>::infinity();
			FlowEdge* pPrevEdge = m_prevTable[sink];

			// 최소 잔여 유량을 찾는다
			while (pPrevEdge != nullptr)
			{
				minResidualCapacity = min(minResidualCapacity,
										  pPrevEdge->GetResidualCapacityTo(pPrevEdge->GetTo()));
				pPrevEdge = m_prevTable[pPrevEdge->GetFrom()];
			}

			pPrevEdge = m_prevTable[sink];

			// 경로의 유량을 최소 잔여 유량만큼 증가시킨다
			while (pPrevEdge != nullptr)
			{
				pPrevEdge->UpdateFlowTo(pPrevEdge->GetTo(), minResidualCapacity);
				pPrevEdge = m_prevTable[pPrevEdge->GetFrom()];
			}

			m_maxFlow += minResidualCapacity;

			Print(flowNet);
		}
	}

	bool IsAugmentingPath(const FlowNetwork& flowNet, int source, int sink)
	{
		fill(m_scheduledTable.begin(), m_scheduledTable.end(), false);

		queue<int> visitScheduler; // BFS

		m_scheduledTable[source] = true;
		visitScheduler.push(source);

		while (visitScheduler.empty() == false)
		{
			int visitedVertex = visitScheduler.front();
			visitScheduler.pop();

			for (FlowEdge* pNeighborEdge : flowNet.GetEdges(visitedVertex))
			{
				int neighborVertex = pNeighborEdge->GetOther(visitedVertex);

				if ((m_scheduledTable[neighborVertex] == false) && 
					(pNeighborEdge->GetResidualCapacityTo(neighborVertex) > 0)) // <- TODO: BFS와의 차이 확인
				{
					m_prevTable[neighborVertex] = pNeighborEdge;
					m_scheduledTable[neighborVertex] = true;
					visitScheduler.push(neighborVertex);
				}
			}
		}

		return m_scheduledTable[sink];
	}

	void Print(FlowNetwork& g)
	{
		cout << "Result:" << endl;
		for (int v = 0; v < g.GetNumVertices(); v++)
			for (FlowEdge* e : g.GetEdges(v))
				if (v == e->GetFrom())
					e->Print();
		cout << m_maxFlow << endl;
	}

private:
	vector<bool>			m_scheduledTable;
	vector<FlowEdge*>		m_prevTable;
	double					m_maxFlow = 0;
};

int main()
{
	// 강의 영상에 나오는 예시
	/*FlowNetwork flowNet(4);

	for (const auto& e : vector<FlowEdge>{ {0, 1, 4.0}, {0, 2, 8.0}, {1, 2, 6.0}, {1, 3, 2.0}, {2, 3, 3.0} })
	{
		flowNet.AddEdge(e);
	}*/

	FlowNetwork flowNet(6); // CLRS 예제
	flowNet.AddEdge({ 0, 1, 16.0 });
	flowNet.AddEdge({ 0, 2, 13.0 });
	flowNet.AddEdge({ 1, 3, 12.0 });
	flowNet.AddEdge({ 2, 1, 4.0 });
	flowNet.AddEdge({ 2, 4, 14.0 });
	flowNet.AddEdge({ 3, 2, 9.0 });
	flowNet.AddEdge({ 3, 5, 20.0 });
	flowNet.AddEdge({ 4, 3, 7.0 });
	flowNet.AddEdge({ 4, 5, 4.0 });

	FordFulkerson f(flowNet, 0, flowNet.GetNumVertices() - 1);

	return 0;
}
