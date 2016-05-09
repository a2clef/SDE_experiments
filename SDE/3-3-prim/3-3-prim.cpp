#include <iostream>
#include <limits.h>
using namespace std;

#define MAX_PC	100


int graph[MAX_PC][MAX_PC];
int lowcost[MAX_PC];
int checked[MAX_PC];
int father[MAX_PC];
int PC,dist;

int main()
{
	/*
	sample input:
	4
	-1 1 4 -1
	1 -1 -1 2
	4 -1 -1 3
	-1 2 3 -1
	
	
	*/
	cout << "Please input PC." << endl;
	cin >> PC;
	cout << "Please input the graph. -1 means not connected" << endl;
	for (int i = 0; i < PC; i++)
		for (int j = 0; j < PC; j++)
		{
			cin >> dist;
			if (dist != -1)
				graph[i][j] = dist;
			else
				graph[i][j] = INT_MAX;	//not connected is max considered not connected.
		};

	int weight=0;
	for (int i = 0; i < PC; i++)
	{
		father[i] = -1;
		lowcost[i] = graph[0][i];		//start from point 0
		checked[i] = 0;
	};
	checked[0] = 1;						//mark the starting point
	father[0] = 0;
	for (int i = 1; i < PC; i++)
	{
		int min = INT_MAX;
		int v = -1;
		for (int j = 0; j < PC; j++)	//find another point in the unchecked points
			if (!checked[j] && lowcost[j] < min)
			{
				min = lowcost[j];
				v = j;
			};
		if (v != -1)
		{
			checked[v] = 1;
			weight += lowcost[v];
			for (int j = 0; j < PC; j++)
				if (!checked[j] && graph[v][j]<lowcost[j])
				{
					lowcost[j] = graph[v][j];
					father[j] = v;
				};
		};
	};


	cout << weight << endl;
	return 0;
};