#include <iostream>
#include <string>

#define MAX_LENGTH_PATTERN 100


int kmp(std::string &input, std::string &pattern)
{
	int length_input = input.length();
	int length_pattern = pattern.length();
	int next[MAX_LENGTH_PATTERN];
	//calculate the next array

	//kmp match using next


	//code  only reachs here if pattern is not found in the string
	return -1;
};



int main()
{
	using namespace std;
	string input, pattern;
	//int next[MAX_LENGTH_PATTERN];

	cout << "Please input the string to search." << endl;
	cin >> input;
	cout << "Please input the pattern string. " << endl;
	cout << "It must be shorter than " << MAX_LENGTH_PATTERN << endl;
	while (1)
	{
		cin >> pattern;

		if (pattern == "exit")
			break;

		if (pattern.length() > MAX_LENGTH_PATTERN)
			cout << "The pattern string is too long, try again." << endl;
		else
			cout << "The position of pattern in string is(-1 means not found): " << kmp(input, pattern) << endl;
	};

	return 0;
}