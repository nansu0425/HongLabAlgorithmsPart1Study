#include "UnionFind.h"
#include <utility>
using namespace std;

int main()
{
	UnionFind uf(4);
	vector<pair<int, int>> testPairs =
	{
		{0, 1}, {1, 2}, {2, 3}, {3, 0}
	};

	uf.Print();

	for (const auto& pair : testPairs)
	{
		int u = pair.first;
		int v = pair.second;
		bool connected = uf.Connected(u, v);  // uf.Find(p) == uf.Find(q);

		cout << u << " " << v << " " << std::boolalpha << connected << endl;
		cout << "Union " << u << " " << v << endl;

		uf.Union(u, v);

		uf.Print();
	}
}
