#include "vector" 
#include "iostream" 
#include "algorithm"

using namespace std;

#define  M 2000              //limit of numbers
int STACK[M], top = 0;       //stack for Tarjan 
bool InStack[M];
int DFN[M];
int Low[M];
int ComponetNumber = 0;      //part count
int Index = 0;
vector <int> Edge[M];        //storages the list 
vector <int> Component[M];

void Tarjan(int i)
{
	//*******************
	if (ComponetNumber > 1)
	{
		return;
	};
	//*******************
	int j;
	DFN[i] = Low[i] = Index++;
	InStack[i] = true;
	STACK[++top] = i;
	for (unsigned int e = 0; e<Edge[i].size(); e++)
	{
		j = Edge[i][e];
		if (DFN[j] == -1)
		{
			Tarjan(j);
			Low[i] = min(Low[i], Low[j]);
		}
		else if (InStack[j])
			Low[i] = min(Low[i], DFN[j]);
	}
	if (DFN[i] == Low[i])
	{
		//cout << "TT    " << i << "   " << Low[i] << endl;
		ComponetNumber++;
		do
		{
			j = STACK[top--];
			InStack[j] = false;
			Component[ComponetNumber].push_back(j);
		} while (j != i);
	}
}

void solve(int N)     //此图中点的个数，注意是0-indexed！ 
{
	memset(STACK, -1, sizeof(STACK));
	memset(InStack, 0, sizeof(InStack));
	memset(DFN, -1, sizeof(DFN));
	memset(Low, -1, sizeof(Low));
	for (int i = 0; i<N; i++)
		if (DFN[i] == -1)
			Tarjan(i);
}
/*
此算法正常工作的基础是图是0-indexed的。
*/
int main()
{
	Edge[0].push_back(1); Edge[0].push_back(2);
	Edge[1].push_back(3);
	Edge[2].push_back(3); Edge[2].push_back(4);
	Edge[3].push_back(0); Edge[3].push_back(5);
	Edge[4].push_back(5);
	int  N = 6;
	solve(N);
	cout << "ComponetNumber is " << ComponetNumber << endl;
	for (int i = 0; i<N; i++)
		cout << Low[i] << " ";
	cout << endl;
	for (int i = 0; i<N; i++)
	{
		for (unsigned int j = 0; j<Component[i].size(); j++)
			cout << Component[i][j];
		cout << endl;
	}
	return 0;
}