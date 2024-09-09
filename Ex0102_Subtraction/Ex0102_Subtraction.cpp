#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
string Subtract(string str1, string str2)
{
	// 둘이 같을 경우 바로 "0" 반환
	if (str1 == str2)
		return "0"; // '0'은 char, "0"은 string

	const int strSize = max(static_cast<int>(str1.size()), static_cast<int>(str2.size()));
	str1 = string(strSize - str1.size(), '0') + str1; // 문자열끼리의 더하기도 가능
	str2 = string(strSize - str2.size(), '0') + str2;

	string result(strSize, '0');

	int carry = 0;

	// 모든 자릿수 빼기 진행
	for (int strIdx = strSize - 1; strIdx >= 0; --strIdx)
	{
		int str1Num = str1[strIdx] - '0';
		int str2Num = str2[strIdx] - '0';

		// 미리 10을 빌려온다
		int sum = str1Num - str2Num + carry + 10; 

		// sum에 10을 더하지 않았을 때 음수면 캐리 값 -1 설정
		carry = sum / 10 - 1;

		result[strIdx] = sum % 10 + '0';
	}

	// result 앞의 0 문자들을 제거
	int validIdx = 0;

	while (result[validIdx] == '0')
	{
		++validIdx;
	}

	result = result.substr(validIdx, strSize - validIdx);

	return result;
}

int main()
{
	// 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
	vector<vector<string>> tests = {
		{"34", "12", std::to_string(34 - 12)}
		, {"123", "45", std::to_string(123 - 45)}
		, {"54544", "44545", std::to_string(54544 - 44545)}
		, {"5555", "55", std::to_string(5555 - 55)}
		, {"5555", "5555", std::to_string(5555 - 5555)}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "8108924688874870000000906000909999"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];
		const string str2 = t[1];
		const string expected = t[2];

		cout << str1 << " - " << str2 << " = " << expected << endl;

		const string result = Subtract(str1, str2);

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
