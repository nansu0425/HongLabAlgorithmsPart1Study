#include <iostream>
#include <string>
using namespace std;

int main()
{
	// 문제 1. 10진수 -> 2진수
	{
		int decimal = 105;
		string binary;

		while (decimal > 0)
		{
			binary = string(1, decimal % 2 + '0') + binary;
			decimal >>= 1;
		}

		cout << binary << endl; // 1101001
	}

	// 문제 2. 문자열 뒤집기
	{
		string input = "Hello, World!";

		int leftIdx = 0;
		int rightIdx = input.size() - 1;

		while (leftIdx < rightIdx)
		{
			char tmp = input[leftIdx];
			input[leftIdx] = input[rightIdx];
			input[rightIdx] = tmp;

			++leftIdx;
			--rightIdx;
		}

		cout << input << endl; // !dlroW ,olleH
	}

	// 문제 3. 모든 자리 다 더하기
	{
		string n = "789789";

		while (n.size() > 1)
		{
			int sum = 0;

			while (n.size() > 0)
			{
				sum += n[0] - '0';
				n = n.substr(1, n.size() - 1);
			}

			n = to_string(sum);
		}

		cout << n << endl;
	}

	return 0;
}
