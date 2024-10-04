#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node
{
	string ch; // char보다 디버깅 편리
	int freq;
	Node* pLeft = nullptr;
	Node* pRight = nullptr;
};

// std::priority_queue에서 사용할 MinHeapNode의 비교
struct Compare
{
	bool operator()(Node* pLeft, Node* pRight)
	{
		return pLeft->freq > pRight->freq;
	}
};

void PrintCodes(Node* root, string str)
{
	if (!root)
		return;

	if (!root->pLeft && !root->pRight) // leaf node이면 출력
		cout << root->ch << ": " << str << "\n";

	PrintCodes(root->pLeft, str + "0");
	PrintCodes(root->pRight, str + "1");
}

void HuffmanCoding(vector<char> charTable, vector<int> freqTable)
{
	// freq가 작을 수록 우선순위가 높은 힙
	// struct Compare에서 우선순위 비교
	priority_queue<Node*, vector<Node*>, Compare> minFreqPriorityQueue;

	for (int charIdx = 0; charIdx < charTable.size(); ++charIdx)
	{
		minFreqPriorityQueue.push(new Node{ string(1, charTable[charIdx]), freqTable[charIdx] });
	}
	
	while (minFreqPriorityQueue.size() > 1)
	{
		Node* pLeft = minFreqPriorityQueue.top();
		minFreqPriorityQueue.pop();

		Node* pRight = minFreqPriorityQueue.top();
		minFreqPriorityQueue.pop();

		Node* pParent = new Node{pLeft->ch + pRight->ch, 
								 pLeft->freq + pRight->freq, 
								 pLeft, 
								 pRight};
		minFreqPriorityQueue.push(pParent);

		cout << "(" << pLeft->ch << ", " << pLeft->freq << ") + (" << pRight->ch << ", " << pRight->freq << ") -> ";
		cout << "(" << pParent->ch << ", " << pParent->freq << ")" << endl;
	}

	PrintCodes(minFreqPriorityQueue.top(), "");
}

int main()
{
	vector<char> charTable = { 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<int> freqTable = { 9, 8, 7, 6, 5, 4};

	HuffmanCoding(charTable, freqTable);

	return 0;
}
