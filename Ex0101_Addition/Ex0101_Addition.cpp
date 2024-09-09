#include <string>
#include <vector>
#include <iostream>

using namespace std;

string Add(string lhs, string rhs)
{
	string result;
	
	int lhsIdx = static_cast<int>(lhs.size()) - 1;
	int rhsIdx = static_cast<int>(rhs.size()) - 1;
	int carry = 0;

	// 인덱스가 모두 0이상일 때 반복
	while ((lhsIdx >= 0) && (rhsIdx >= 0))
	{
		int sum = lhs[lhsIdx] + rhs[rhsIdx] - 2 * '0' + carry;

		carry = sum / 10;
		result = string(1, sum % 10 + '0') + result;

		--lhsIdx;
		--rhsIdx;
	}

	int resultIdx = -1;

	// 더하지 않고 남은 문자열을 더한다
	if (lhsIdx >= 0)
	{
		result = lhs.substr(0, lhsIdx + 1) + result;
		resultIdx = lhsIdx;
	}
	else if (rhsIdx >= 0)
	{
		result = rhs.substr(0, rhsIdx + 1) + result;
		resultIdx = rhsIdx;
	}

	// 캐리 처리
	if (carry == 1)
	{
		while ((resultIdx >= 0) && (result[resultIdx] == '9'))
		{
			result[resultIdx] = '0';
			--resultIdx;
		}

		if (resultIdx == -1)
		{
			result = string(1, '1') + result;
		}
		else
		{
			result[resultIdx] = result[resultIdx] + 1;
		}
	}

	return result;
}

int main()
{
	vector<vector<string>> tests = {
		{"12", "34", to_string(12 + 34)}
		, {"123", "45", to_string(123 + 45)}
		, {"54544", "44545", to_string(54544 + 44545)}
		, {"5555", "55", to_string(5555 + 55)}
		, {"5555", "5555", to_string(5555 + 5555)}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "11538017781967960909090003089999089"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];     // "12"
		const string str2 = t[1];     // "34"
		const string expected = t[2]; // "46"

		cout << str1 << " + " << str2 << " = " << expected << endl;

		const string result = Add(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK" << endl;
		else {
			cout << "Not OK" << endl;
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}
