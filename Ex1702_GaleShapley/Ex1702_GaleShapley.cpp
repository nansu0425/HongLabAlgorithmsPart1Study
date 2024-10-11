#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <cassert>
using namespace std;

struct Vertex
{
	string			name = "";
	vector<string>	priority; // 선호도 우선순위
	int				matchedRank = -1; // 현재 자신의 몇 "순위"와 연결되어 있는지 기록

	int GetRank(string name)
	{
		for (int rank = 0; rank < priority.size(); rank++)
		{
			if (priority[rank] == name) 
			{
				return rank;
			}
		}

		assert(false);

		return -1;

		// Rank() 반환값이 작을 수록 우선순위가 높다
		// unordered_map<이름, 우선순위>를 만들어서 더 빠르게 확인 가능
	}

	string GetMatchedName()
	{
		if (matchedRank == -1) 
		{
			return "NA";
		}
		
		return priority[matchedRank];	
	}

	void Print()
	{
		cout << name << "(";
		for (auto& p : priority)
			cout << p;
		cout << ")";
	}
};

void Print(map<string, Vertex>& interns, unordered_map<string, Vertex>& teams)
{
	for (auto& i : interns)
	{
		i.second.Print();
		cout << " - ";
		if (i.second.matchedRank == -1)
			cout << "No Team";
		else {
			teams[i.second.GetMatchedName()].Print();
			if (i.second.name != teams[i.second.GetMatchedName()].GetMatchedName())
				cout << "*"; // 서로 연결이 아니라면 임시라는 의미로 * 추가
		}
		cout << endl;
	}
}

int main()
{
	map<string, Vertex> interns; // 디버깅할때 순서대로 보기 위해 map 사용, unordered_map 사용 가능
	interns["A"] = Vertex{ "A", {"X", "Y", "Z"} };
	interns["B"] = Vertex{ "B", {"Y", "X", "Z"} };
	interns["C"] = Vertex{ "C", {"Y", "Z", "X"} };

	unordered_map<string, Vertex> teams;
	teams["X"] = Vertex{ "X", {"B", "A", "C"} };
	teams["Y"] = Vertex{ "Y", {"A", "B", "C"} };
	teams["Z"] = Vertex{ "Z", {"B", "C", "A"} };
	//teams["X"] = Vertex{ "X", {"B", "A", "C"} };
	//teams["Y"] = Vertex{ "Y", {"A", "C", "B"} };
	//teams["Z"] = Vertex{ "Z", {"B", "C", "A"} };

	queue<Vertex*> ptrsUnmatchedIntern;

	for (auto& intern : interns)
	{
		ptrsUnmatchedIntern.push(&intern.second); // 모든 인턴을 free 큐에 넣기
	}

	while (ptrsUnmatchedIntern.empty() == false)
	{
		Vertex* ptrUnmatchedIntern = ptrsUnmatchedIntern.front();
		ptrsUnmatchedIntern.pop();

		cout << "Intern " << ptrUnmatchedIntern->name << endl;
		
		// 인턴이 가장 선호하는 팀과 매치
		ptrUnmatchedIntern->matchedRank += 1;
		Vertex* ptrPreferedTeam = &teams[ptrUnmatchedIntern->GetMatchedName()];

		// 팀에 매칭된 인턴이 없었던 경우
		if (ptrPreferedTeam->matchedRank == -1)
		{
			ptrPreferedTeam->matchedRank = ptrPreferedTeam->GetRank(ptrUnmatchedIntern->name);
		}
		// 팀에 이미 매칭된 팀이 있는 경우 팀의 우선순위에 따라 인턴 한 명 선택
		else
		{
			if (ptrPreferedTeam->GetRank(ptrUnmatchedIntern->name) < ptrPreferedTeam->matchedRank)
			{
				ptrsUnmatchedIntern.push(&interns[ptrPreferedTeam->GetMatchedName()]);
				ptrPreferedTeam->matchedRank = ptrPreferedTeam->GetRank(ptrUnmatchedIntern->name);
			}
			else
			{
				ptrsUnmatchedIntern.push(ptrUnmatchedIntern);
			}
		}

		Print(interns, teams);
	}

	return 0;
}
