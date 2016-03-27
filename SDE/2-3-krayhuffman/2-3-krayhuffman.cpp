#include <iostream>
#include <vector>
#include <conio.h>	//this header may cause problem.
#include <string>
#include <fstream>
#include <algorithm>
/*
 an implementation of kay ray huffman tree.
 using vector as mem controlling tool to storage all nodes

*/

using namespace std;
#define INPUT_FILENAME		"phaedo.txt"		//this place defines the article used to encode
#define MAX_VALUE			2147483647			//max value of int, used to find the lease weight node in the list
#define MAX_CODE			300
#define MAX_RAY				10
vector<int> temp_Code;


int add(int k,int count)
{
	int y = count % (k - 1);
	if (y == 0) return 1;
	if (y == 1) return 0;
	return k - y;
};


class HTNode
{
public:
	int weight;
	int end;
	char key;
	HTNode* offsprings[MAX_RAY];
	bool operator >(HTNode &second)
	{
		return weight < second.weight;
	};
	bool operator <(HTNode &second)
	{
		return weight > second.weight;
	};
	bool operator ==(HTNode &second)
	{
		return weight == second.weight;
	};
};

void KHT_DFS(HTNode* p,int ray)
{
	if (p->end)
	{
		for (unsigned int i = 0; i < temp_Code.size(); i++) cout << temp_Code[i];
		cout << " ";
		cout << p->key << " " << p->weight << endl;
		return;
	};
	for (int i = 0; i < ray; i++)
	{
		temp_Code.push_back(i);
		KHT_DFS(p->offsprings[i], ray);
		temp_Code.pop_back();
	};
	return;
};

int main()
{
	int ray;
	int code_Count = 0;
	HTNode set[MAX_CODE];
	ifstream fin(INPUT_FILENAME);				//open the file
	if (!fin.is_open())
	{
		cout << "This file doesnt exist, the program will now exit." << endl;
		return 0;
	};

	cout << "Please input k." << endl<<">>";
	cin >> ray;
	while (!fin.eof())
	{
		char temp_Char;
		int temp_Pos=-1;
		fin.get(temp_Char);
		for (int i=0; i < code_Count;i++)
			if (set[i].key == temp_Char)
			{
				set[i].weight++;
				temp_Pos = i;
				break;
			};
		if (temp_Pos == -1)
		{
			HTNode temp_Node;
			temp_Node.end = 1;
			temp_Node.key = temp_Char;
			temp_Node.weight = 1;
			set[code_Count]=temp_Node;
			code_Count++;
		};
	};
	sort(set, set+code_Count);

	cout << "File successfully readed. The initialized result is:" << endl;

	for (int i = 0; i < code_Count; i++)
	{
		cout << set[i].key << " " << set[i].weight << endl;
	};
	
	cout << "Now building tree." << endl;
	for (int i = 0; i < add(ray, code_Count); i++)
	{
		HTNode temp_Node;
		temp_Node.end = 1;
		temp_Node.key = 0;
		temp_Node.weight = 0;
		set[code_Count]=temp_Node;
		code_Count++;
	};

	while (code_Count > 1)
	{
		HTNode* p;
		sort(set, set+code_Count);
		HTNode temp_Node;
		temp_Node.end = 0;
		temp_Node.key = 0;
		temp_Node.weight = 0;
		for (int i =0; i < ray; i++)
		{
			temp_Node.weight += set[code_Count - i - 1].weight;
			p = new HTNode;
			*p = set[code_Count - i - 1];
			temp_Node.offsprings[i] = p;
		};
		code_Count -= ray - 1;
		set[code_Count - 1] = temp_Node;
	};

	KHT_DFS(&set[0], ray);				//display all code in the huffman tree.

	cout << "Now input the code to decode" << endl;
	HTNode* ptr_Position = &set[0];
	while (1)
	{
		char temp_Char;
		int choice;
		temp_Char = _getch();
		choice = temp_Char - '0';
		if (choice >= ray)
		{
			cout << "exceed the limit of rays. retry" << endl;
			continue;
		};
		ptr_Position = ptr_Position->offsprings[choice];
		if (ptr_Position->end)
		{
			cout<< ptr_Position->key << endl;
			ptr_Position = &set[0];
		};
	};



	return 0;
};
