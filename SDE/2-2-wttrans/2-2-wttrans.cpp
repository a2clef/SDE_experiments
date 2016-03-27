#include <iostream>
#include <stdio.h>
#include <vector>


#define MAXIMUM_NODE_COUNT 100

using namespace std;
int Element_Count;
/*
Arr_Mid stores the Mid-Order sequence
Arr_Pre stores the Pre-Order sequence
*/
int Arr_Mid[MAXIMUM_NODE_COUNT], Arr_Pre[MAXIMUM_NODE_COUNT];


class PTNode
{
public:
	int Key_Value;
	vector<PTNode*> offspring;
};



class BiTNode					//The node of a tree
{
public:
	BiTNode* Child_L;
	BiTNode* Child_R;
	int Key_Value;
};

BiTNode* Tree_Build_Recursive(int Pa, int Ma, int Len)
/*
Build a binary tree using Arr_Pre and Arr_Mid
Method: Recursive
*/
{
	if (Len == 0)						//return NULL if no root node
		return NULL;
	int Temp, Pos_root;					//Temp=Value of root node
	BiTNode* Ptr_Temp;
	Temp = Arr_Pre[Pa];
	for (int i = Ma; i < Ma + Len; i++)	//Pos_root=position of root node in Arr_Mid
		if (Arr_Mid[i] == Temp)
		{
			Pos_root = i;
			break;
		};
	Ptr_Temp = new BiTNode;
	Ptr_Temp->Key_Value = Temp;			//split Arrs into 2 parts as left and right sub_tree
	Ptr_Temp->Child_L = Tree_Build_Recursive(Pa + 1, Ma, Pos_root - Ma);
	Ptr_Temp->Child_R = Tree_Build_Recursive(Pa + Pos_root - Ma + 1, Pos_root + 1, Len - Pos_root + Ma - 1);
	return Ptr_Temp;
};

void Tree_Walk_PreOrder_Recursive(BiTNode* Ptr_Root)
/*
Walk the tree in Pre-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	cout << Ptr_Root->Key_Value << ' ';
	Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_L);
	Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_MidOrder_Recursive(BiTNode* Ptr_Root)
/*
Walk the tree in Mid-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_L);
	cout << Ptr_Root->Key_Value << ' ';
	Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_SucOrder_Recursive(BiTNode* Ptr_Root)
/*
Walk the tree in Succ-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_L);
	Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_R);
	cout << Ptr_Root->Key_Value << ' ';
	return;
};


PTNode* make_Tree(BiTNode* root)
{
	if (root->Child_L)
	{
		PTNode* temp_PTNode = new PTNode;
		temp_PTNode->Key_Value = root->Key_Value;
		vector<BiTNode*> newoffs;
		BiTNode* temp_BiTPtr=root->Child_L;
		while (temp_BiTPtr)
		{
			BiTNode* next = temp_BiTPtr->Child_R;
			newoffs.push_back(temp_BiTPtr);
			temp_BiTPtr->Child_R = NULL;
			temp_BiTPtr = next;
		};
		for (unsigned int i = 0; i < newoffs.size(); i++)
			temp_PTNode->offspring.push_back(make_Tree(newoffs[i]));
		return temp_PTNode;
	}
	else
	{
		PTNode* temp_PTNode = new PTNode;
		temp_PTNode->Key_Value = root->Key_Value;
		return temp_PTNode;	
	};
};

BiTNode* make_BiT(PTNode* root)
{
	BiTNode* temp_BiTNode = new BiTNode;
	temp_BiTNode->Key_Value = root->Key_Value;
	temp_BiTNode->Child_L = NULL;
	temp_BiTNode->Child_R = NULL;
	if (root->offspring.size())		//if this tree node does have offsprings
	{
		temp_BiTNode->Child_L = make_BiT(root->offspring[0]);
		BiTNode* pos_BiTNode = temp_BiTNode->Child_L;
		for (unsigned int i = 1; i < root->offspring.size(); i++)
		{
			pos_BiTNode->Child_R = make_BiT(root->offspring[i]);
			pos_BiTNode = pos_BiTNode->Child_R;
		};
	};
	return temp_BiTNode;
};

BiTNode* comb_wood(BiTNode* set[] , int count )
{
	for (int i = 0; i < count-1; i++)
		set[i]->Child_R = set[i + 1];
	return set[0];
};

int main()
{

	cout << "NOTICE:ALL ELEMENT INPUT IN THE TREE SHOULD BE UNIQUE." << endl;
	cout << "A POSSIBLE INPUT EXAMPLE:" << endl;
	cout << "8" << endl;
	cout << "1 2 4 7 3 5 6 8" << endl;
	cout << "4 7 2 1 5 3 8 6" << endl << endl;

	cout << "Please input the size of the tree:";
	cin >> Element_Count;

	cout << "Please input the Pre-order array(seprate with while spaces):" << endl;
	for (int i = 0; i < Element_Count; i++)
		cin >> Arr_Pre[i];

	cout << "Please input the Mid-order array(seprate with white spaces):" << endl;
	for (int i = 0; i < Element_Count; i++)
		cin >> Arr_Mid[i];
	cout << endl;

	BiTNode* Root_Ptr = NULL;

	Root_Ptr = Tree_Build_Recursive(0, 0, Element_Count);

	BiTNode* temp_Ptr=Root_Ptr;
	BiTNode* BiTList[100];
	PTNode* PTList[100];
	int BiTCount = 0;
	while (temp_Ptr)
	{
		BiTList[BiTCount] = temp_Ptr;
		BiTCount++;
		temp_Ptr = temp_Ptr->Child_R;
	};

	for (int i = 0; i < BiTCount; i++)
	{
		BiTList[i]->Child_R = NULL;
		//--------------
		//cout << endl;
		//Tree_Walk_PreOrder_Recursive(BiTList[i]);
		
		PTList[i] = make_Tree(BiTList[i]);
	};

	//-------------add some display here

	BiTNode* new_BiTList[100];

	for (int i=0; i < BiTCount; i++)
		new_BiTList[i] = make_BiT(PTList[i]);

	BiTNode* new_Root_Ptr = comb_wood(new_BiTList, BiTCount);

	Tree_Walk_PreOrder_Recursive(new_Root_Ptr);
	cout << endl;
	Tree_Walk_MidOrder_Recursive(new_Root_Ptr);
	cout << "All process is done!Excited!" << endl;

	return 0;
};