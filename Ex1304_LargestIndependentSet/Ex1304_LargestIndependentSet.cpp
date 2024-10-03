#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node
{
public:
	int value = 0;
	int memo = 0; // <- Memoization에 사용
	Node* pLeft = nullptr;
	Node* pRight = nullptr;

	// 꼭 이진 트리가 아니라 싸이클이 없는 트리 구조면 다 가능합니다.
};

int RecurLIS(Node* pRoot)
{
	if (pRoot == nullptr)
	{
		return 0;
	}

	// case1: Root 노드가 포함 되지 않는 경우엔 자식들 포함 가능
	int case1 = RecurLIS(pRoot->pLeft) + RecurLIS(pRoot->pRight);

	// case2: Root 노드가 포함되는 경우는 하나 건너서 자식들의 자식들만 포함 가능
	int case2 = 1;

	if (pRoot->pLeft != nullptr)
	{
		case2 += RecurLIS(pRoot->pLeft->pLeft) + RecurLIS(pRoot->pLeft->pRight);
	}

	if (pRoot->pRight != nullptr)
	{
		case2 += RecurLIS(pRoot->pRight->pLeft) + RecurLIS(pRoot->pRight->pRight);
	}

	// 두 가지 경우 중 큰 경우 반환
	return max(case1, case2);
}

int MemoLIS(Node* pRoot)
{
	if (pRoot == nullptr)
	{
		return 0;
	}

	if (pRoot->memo > 0)
	{
		return pRoot->memo;
	}
	
	// case1: Root 노드가 포함 되지 않는 경우엔 자식들 포함 가능
	int case1 = MemoLIS(pRoot->pLeft) + MemoLIS(pRoot->pRight);

	// case2: Root 노드가 포함되는 경우는 하나 건너서 자식들의 자식들만 포함 가능
	int case2 = 1;

	if (pRoot->pLeft != nullptr)
	{
		case2 += MemoLIS(pRoot->pLeft->pLeft) + MemoLIS(pRoot->pLeft->pRight);
	}

	if (pRoot->pRight != nullptr)
	{
		case2 += MemoLIS(pRoot->pRight->pLeft) + MemoLIS(pRoot->pRight->pRight);
	}

	pRoot->memo = max(case1, case2);

	return pRoot->memo;
}

Node* MakeNode(int value)
{
	Node* temp = new Node();
	temp->value = value;
	temp->pLeft = temp->pRight = nullptr;
	return temp;
}

int main()
{
	// 이진 트리 만들기
	Node* pRoot = MakeNode(1);
	pRoot->pLeft = MakeNode(2);
	pRoot->pLeft->pLeft = MakeNode(4);
	pRoot->pLeft->pRight = MakeNode(5);
	pRoot->pLeft->pRight->pLeft = MakeNode(7);
	pRoot->pLeft->pRight->pRight = MakeNode(8);
	pRoot->pRight = MakeNode(3);
	pRoot->pRight->pRight = MakeNode(6);

	cout << RecurLIS(pRoot) << endl;
	cout << MemoLIS(pRoot) << endl;

	return 0;
}

// GeeksForGeeks 예제를 약간 변형하였습니다.
// https://www.geeksforgeeks.org/largest-independent-set-problem-using-dynamic-programming/
