#include <string>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

string Multiply(string left, string right)
{
	// 둘 중에 하나라도 "0"이면 "0"반환
	if ((left == "0") || (right == "0"))
	{
		return "0";
	}

	// left에 더 긴 숫자가 오도록 한다
	if (left.size() < right.size())
	{
		std::swap(left, right);
	}

	std::string result;
	int offset = 0;

	for (int rightIdx = right.size() - 1; rightIdx >= 0; --rightIdx)
	{
		int mulCarry = 0;
		int sumCarry = 0;
		int resultIdx = result.size() - 1 - offset;
		++offset;

		// right의 한 자리 숫자와 left의 곱을 result에 더한다
		for (int leftIdx = left.size() - 1; leftIdx >= 0; --leftIdx)
		{
			// 곱과 캐리를 구한다
			int mul = (left[leftIdx] - '0') * (right[rightIdx] - '0') + mulCarry;
			mulCarry = mul / 10;

			// 곱을 더한다
			if (resultIdx < 0)
			{
				int sum = mul % 10 + sumCarry;
				sumCarry = sum / 10;

				result = std::string(1, sum % 10 + '0') + result;
			}
			else
			{
				int sum = result[resultIdx] + mul % 10 + sumCarry - '0';
				sumCarry = sum / 10;
				
				result[resultIdx] = sum % 10 + '0';
				--resultIdx;
			}
		}

		int carry = 0;

		// 캐리 처리
		if (mulCarry + sumCarry > 0)
		{
			if (resultIdx >= 0)
			{
				int sum = result[resultIdx] + mulCarry + sumCarry - '0';
				
				carry = sum / 10;
				result[resultIdx] = sum % 10 + '0';
			}
			else
			{
				int sum = mulCarry + sumCarry;

				carry = sum / 10;
				result = std::string(1, sum % 10 + '0') + result;
			}
		}

		if (carry > 0)
		{
			result = std::string(1, carry + '0') + result;
		}
	}

	//for (int rightIdx = right.size() - 1; rightIdx >= 0; --rightIdx)
	//{
	//	std::string mul;
	//	int mulCarry = 0;

	//	// right의 한 자리와 left의 곱을 mul에 저장
	//	for (int leftIdx = left.size() - 1; leftIdx >= 0; --leftIdx)
	//	{
	//		int mulNum = (left[leftIdx] - '0') * (right[rightIdx] - '0') + mulCarry;

	//		mulCarry = mulNum / 10;
	//		mul = std::string(1, mulNum % 10 + '0') + mul;
	//	}

	//	// 캐리 처리
	//	if (mulCarry > 0)
	//	{
	//		mul = std::string(1, mulCarry + '0') + mul;
	//		mulCarry = 0;
	//	}

	//	// mul을 처음 더할 때 더하지 않고 result로 이동
	//	if (result == "")
	//	{
	//		result = std::move(mul);
	//		continue;
	//	}

	//	int mulIdx = mul.size() - 1;
	//	int resultIdx = result.size() - 1 - offset;
	//	++offset;

	//	// result에 mul을 더한다
	//	while (resultIdx >= 0)
	//	{
	//		int sum = result[resultIdx] + mul[mulIdx] + mulCarry - 2 * '0';

	//		mulCarry = sum / 10;
	//		result[resultIdx] = sum % 10 + '0';

	//		--resultIdx;
	//		--mulIdx;
	//	}

	//	// 더하지 않은 mul의 숫자 처리
	//	if (mulIdx >= 0)
	//	{
	//		int sum = mul[mulIdx] + mulCarry - '0';

	//		mulCarry = sum / 10;
	//		result = std::string(1, sum % 10 + '0') + result;
	//	}

	//	// 캐리 처리
	//	if (mulCarry == 1)
	//	{
	//		result = std::string(1, '1') + result;
	//	}
	//}

	return result;
}

int main()
{
	vector<vector<string>> tests = {
		{"12", "34", std::to_string(12 * 34)},
		{"123", "45", std::to_string(123 * 45)},
		{"5555", "55", std::to_string(5555 * 55)},
		{"5555", "5555", std::to_string(5555 * 5555)},
		{"98234712354214154", "171454654654655", "16842798681791158832220782986870"}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "16842798681791114273590624445460185389471221520083884298838480662480"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];
		const string str2 = t[1];
		const string expected = t[2];

		cout << str1 << " * " << str2 << " = " << expected << endl;

		const string result = Multiply(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK";
		else {
			cout << "Not OK";
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}
