#include "vector" 
#include "iostream" 
#include "algorithm"

using namespace std;

#define  M 2000              //limit of numbers
int STACK[M], top = 0;       //stack for Tarjan 
bool InStack[M];           
int DFN[M];                  
int Low[M];                   
int ComponentNumber = 0;      //part count
int Index = 0;             
int N;
vector <int> Edge[M];        //storages the list 
/*
4
1 2
2 3
3 4
4 1
-1 -1

4
1 2
2 3
1 4
4 3
-1 -1


*/

void Tarjan(int i)
{
	if (ComponentNumber > 1)
		return;

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
		ComponentNumber++;
		do
		{
			j = STACK[top--];
			InStack[j] = false;
		} while (j != i);
	}
}


int main()
{

	cout << "Please input the number of points in the graph.(below " << M << ")." << endl;
	cin >> N;

	cout << "Please input edges.(input -1 -1 to exit loop)" << endl;
	while (1)
	{
		//please there's no data check here.
		int i, j;
		cin >> i >> j;
		if (i == -1)
			break;
		Edge[i-1].push_back(j-1);
	};

	memset(STACK, -1, sizeof(STACK));
	memset(InStack, 0, sizeof(InStack));
	memset(DFN, -1, sizeof(DFN));
	memset(Low, -1, sizeof(Low));

	Tarjan(0);

	for (int i = 0; i < N; i++)
		if (DFN[i] == -1)
		{
			cout << "This is not a strongly connected graph." << endl;
			goto FINISH;
		};
	
	if (ComponentNumber > 1)
		cout << "This is not a strongly connected graph." << endl;
	else
		cout << "This is a strongly connected graph." << endl;
FINISH:
	return 0;
}