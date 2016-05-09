#include<iostream>
#include<algorithm>

using namespace std;

#define MAX_EC 1000
int father[MAX_EC], son[MAX_EC];
int PC, EC;
/*
sample input:
4 4
1 2 1
2 4 2
3 4 3
1 3 4


*/
typedef struct 
{
	int a;
	int b;
	int value;
} edgeType;

bool cmp(const edgeType & a, const edgeType & b)
{
	return a.value < b.value;
}

int unionsearch(int x) 
{
	return x == father[x] ? x : unionsearch(father[x]);
}

bool join(int x, int y) 
{
	int root1, root2;
	root1 = unionsearch(x);
	root2 = unionsearch(y);
	if (root1 == root2) 
		return false;
	else if (son[root1] >= son[root2])
	{
		father[root2] = root1;
		son[root1] += son[root2];
	}
	else
	{
		father[root1] = root2;
		son[root2] += son[root1];
	}
	return true;
}

int main()
{
	int E_Count, sum, flag;
	edgeType edge[MAX_EC];

	cin >> PC >> EC;
	E_Count = 0, sum = 0, flag = 0;
	for (int i = 1; i <= PC; ++i)			//initialize
	{
		father[i] = i;
		son[i] = 1;
	}
	for (int i = 1; i <= EC; ++i)
		cin >> edge[i].a >> edge[i].b >> edge[i].value;

	sort(edge + 1, edge + 1 + EC, cmp);		//sort the edges
	for (int i = 1; i <= EC; ++i)
	{
		if (join(edge[i].a, edge[i].b))
		{
			E_Count++;	
			sum += edge[i].value;
		}
		if (E_Count == PC - 1)				//already have enough edges
		{
			flag = 1;
			break;
		}
	}
	if (flag) cout << sum << endl;
	else cout << "ERROR" << endl;

	return 0;
}