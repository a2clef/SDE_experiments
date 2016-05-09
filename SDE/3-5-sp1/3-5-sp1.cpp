#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
/*
an implementation of SPFA
can deal with negative edges.

4
0
0 1 1
1 2 2
2 3 3
0 3 4
-1 -1 -1

*/

using namespace std;

#define M 2000

int ROOT=0;
vector <int> Edge[M];
vector <int> Weight[M];
int N;
int sp[M];				//shortest path
int father[M];			//source
int iQCount[M];
bool inQueue[M];
queue<int> q;



int main()
{
	cout << "Please input the number of points in the graph.(below " << M << ")." << endl;
	cin >> N;

	cout << "Please input the source point." << endl;
	cin >> ROOT;

	cout << "Please input edges.(input -1 -1 -1 to exit loop)" << endl;
	while (1)
	{
		//please there's no data check here.
		int i, j,w;
		cin >> i >> j>>w;
		if (i == -1)
			break;
		Edge[i].push_back(j);
		Edge[j].push_back(i);
		Weight[i].push_back(w);
		Weight[j].push_back(w);
	};
	for (int i = 0; i < N; i++)
	{
		sp[i] = INT_MAX;
		inQueue[i] = false;
		iQCount[i] = 0;
	};
	sp[ROOT] = 0;			//set the source point;
	q.push(ROOT);
	inQueue[ROOT] = true;
	iQCount[ROOT] = 1;
	int OK = 1;
	while (!q.empty())
	{
		int head = q.front();
		q.pop();
		inQueue[head] = false;

		for (unsigned int i = 0; i < Edge[head].size(); i++)	//enum all points connected to head
		{
			int p = Edge[head][i];	//the edge connected to p
			if (sp[head] + Weight[head][i] < sp[p])	//update SP
			{
				sp[p] = sp[head] + Weight[head][i]; //loose!
				if (!inQueue[p])  
				{
					inQueue[p] = true;   
					iQCount[p]++;     
					q.push(p);  
					if (iQCount[p] > N)  //have negative loop
					{
						OK = 0;
						goto FINISH;
					};
				}
			};
		};
	};
FINISH:
	if (OK)
	{
		for (int i = 0; i < N; i++)
			cout << sp[i] << " ";
		cout << endl;
	}
	else
	{
		cout << "Error." << endl;
	};

	return 0;
};