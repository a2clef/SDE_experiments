#include "vector" 
#include "iostream" 
#include "algorithm"

using namespace std;

#define  M 2000              //limit of numbers
#define ROOT 0
//int STACK[M], top = 0;       //stack for Tarjan 
//bool InStack[M];
int DFN[M];
int Low[M];
int HaveCP = 0;      //have a crucial point
int Index = 0;
int N;
vector <int> Edge[M];        //storages the list 


void Tarjan(int i)
{
	if (HaveCP)						//if already found a crucial point, all process can be exited
		return;

	int j;
	int subTreeCount = 0;
	DFN[i] = Low[i] = Index++;			//mark order visited using DFS
	//InStack[i] = true;					//mark visited using DFS
	//STACK[++top] = i;					//put the point in STACK
	for (unsigned int e = 0; e<Edge[i].size(); e++)	//for (every point j connected to i)
	{
		j = Edge[i][e];					//if j is not visited, DFS it
		if (DFN[j] == -1)
		{
			subTreeCount++;
			Tarjan(j);
			Low[i] = min(Low[i], Low[j]);	//after j is visited, update Low[i]
			//***************************************
			if (i == ROOT && subTreeCount > 1)
				HaveCP = 1;
			if (i!= ROOT && Low[j]>=DFN[i])
				HaveCP = 1;
			//***************************************
		}
		else //if (InStack[j])			//if j is already visited, and still in stack
			Low[i] = min(Low[i], DFN[j]);
	}

	/*
	//check if the point is a crucial point
	if (DFN[i] == Low[i])				//in this case, this point cant go to higher point
	{
		HaveCP++;
		do
		{
			j = STACK[top--];
			InStack[j] = false;
		} while (j != i);
	}*/
};


int main()
{

	cout << "Please input the number of points in the graph.(below " << M << ")." << endl;
	cin >> N;

	cout << "Please input connected points.(input -1 -1 to exit loop)" << endl;
	while (1)
	{
		//please there's no data check here.
		int i, j;
		cin >> i >> j;
		if (i == -1)
			break;
		Edge[i - 1].push_back(j - 1);
		Edge[j - 1].push_back(i - 1);
	};

	//memset(STACK, -1, sizeof(STACK));
	//memset(InStack, 0, sizeof(InStack));
	memset(DFN, -1, sizeof(DFN));
	memset(Low, -1, sizeof(Low));

	Tarjan(ROOT);

	for (int i = 0; i < N; i++)
		if (DFN[i] == -1)
		{
			cout << "This is not a bi-connected graph." << endl;
			goto FINISH;
		};

	if (HaveCP)
		cout << "This is not a bi-connected graph." << endl;
	else
		cout << "This is a bi-connected graph." << endl;
FINISH:
	return 0;
}