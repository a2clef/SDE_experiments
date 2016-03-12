#include <iostream>
#include <string>

#define MAX_LENGTH_PATTERN 100


int kmp(std::string &input, std::string &pattern)
{
	int length_input = input.length();
	int length_pattern = pattern.length();
	int next[MAX_LENGTH_PATTERN];
	int position = 0;
	//calculate the next array
	/*
	SOME THING MAGIC HAPPENS HERE
	TAKES ME 10 MINUTES TO UNDERSTAND ONLY ONE LINE OF CODE
	*/
	int max_match = 0;
	next[0] = 0;
	for (int i = 1; i < length_pattern; i++)
	{
		/*
		the magic while loop
		if the new character mismatched, 
		*/
		while (max_match && (pattern[i] != pattern[max_match])) 
			max_match = next[max_match - 1]; 

		if (pattern[i] == pattern[max_match])
			max_match++;
		next[i] = max_match;
	};
	//==================
	std::cout << "The next array for the pattern is:" << std::endl;
	for (int i = 0; i < length_pattern; i++) std::cout << next[i] << " ";
	std::cout << std::endl;
	//kmp match using next
	for (int i = 0; i < length_input; i++)
	{
		while (position && pattern[position] != input[i])
			position = next[position - 1];
		if (pattern[position] == input[i])
			position++;
		if (position == length_pattern)
		return (i - length_pattern + 1);
	}
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