#include <iostream>
#include <stdio.h>

#define MAXIMUM_NODE_COUNT 100
/*
	This program is based on BIT
	added the feature of threading
	*/



using namespace std;
int Element_Count;
/*
Arr_Mid stores the Mid-Order sequence
Arr_Pre stores the Pre-Order sequence
*/
int Arr_Mid[MAXIMUM_NODE_COUNT], Arr_Pre[MAXIMUM_NODE_COUNT];



class TNode					//The node of a tree
{
public:
	TNode* Father;
	TNode* Child_L;
	TNode* Child_R;
	char ltag, rtag;
	int Key_Value;
};
TNode* Previous = NULL;
TNode* Tree_Build_Recursive(int Pa, int Ma, int Len)
/*
Build a binary tree using Arr_Pre and Arr_Mid
Method: Recursive
*/
{
	if (Len == 0)						//return NULL if no root node
		return NULL;
	int Temp, Pos_root;					//Temp=Value of root node
	TNode* Ptr_Temp;
	Temp = Arr_Pre[Pa];
	for (int i = Ma; i < Ma + Len; i++)	//Pos_root=position of root node in Arr_Mid
		if (Arr_Mid[i] == Temp)
		{
			Pos_root = i;
			break;
		};
	Ptr_Temp = new TNode;
	Ptr_Temp->ltag = 0;			//*************newly added*************
	Ptr_Temp->rtag = 0;
	Ptr_Temp->Father = NULL;
	Ptr_Temp->Key_Value = Temp;			//split Arrs into 2 parts as left and right sub_tree
	Ptr_Temp->Child_L = Tree_Build_Recursive(Pa + 1, Ma, Pos_root - Ma);
	if (Ptr_Temp->Child_L != NULL)
		(Ptr_Temp->Child_L)->Father = Ptr_Temp;
	Ptr_Temp->Child_R = Tree_Build_Recursive(Pa + Pos_root - Ma + 1, Pos_root + 1, Len - Pos_root + Ma - 1);
	if (Ptr_Temp->Child_R != NULL)
		(Ptr_Temp->Child_R)->Father = Ptr_Temp;
	return Ptr_Temp;
};


void Tree_Walk_PreOrder_Recursive(TNode* Ptr_Root)
/*
Walk the tree in Pre-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	//--------------
	//cout << Ptr_Root->Key_Value << ' ';
	if (!Ptr_Root->Child_L)
	{
		Ptr_Root->ltag = 1;
		Ptr_Root->Child_L = Previous;
	}
	if (!Previous->Child_R)
	{
		Previous->rtag = 1;
		Previous->Child_R = Ptr_Root;
	}
	Previous = Ptr_Root;

	//--------------
	if (!Ptr_Root->ltag) Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_L);
	if (!Ptr_Root->rtag) Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_PreOrder_Thread(TNode* Head)
{
	TNode* p = Head->Child_R;
	int remain = Element_Count;
	while (remain)
	{
		cout << p->Key_Value << ' ';
		remain--;
		if (!p->ltag) p = p->Child_L;
		else p = p->Child_R;
	};
	cout << endl;
	return;
};


void Tree_Walk_MidOrder_Recursive(TNode* Ptr_Root)
/*
Walk the tree in Mid-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	if (!Ptr_Root->ltag) Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_L);
	//--------------
	//cout << Ptr_Root->Key_Value << ' ';
	if (!Ptr_Root->Child_L)
	{
		Ptr_Root->ltag = 1;
		Ptr_Root->Child_L = Previous;
	}
	if (!Previous->Child_R)
	{
		Previous->rtag = 1;
		Previous->Child_R = Ptr_Root;
	}
	Previous = Ptr_Root;

	//--------------
	if (!Ptr_Root->rtag) Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_MidOrder_Thread(TNode* Head)
{
	TNode* p;
	p = Head->Child_R;                          
	int remain = Element_Count;
	while (remain)                              
	{
		while (p->ltag == 0)                       
		{
			p = p->Child_L;
		}
		cout << p->Key_Value << " ";              
		remain--;
		while (p->rtag == 1 && p->Child_R)
		{
			p = p->Child_R;
			cout << p->Key_Value << " ";
			remain--;
		}

		p = p->Child_R;                
	}
	cout << endl;
};

void Tree_Walk_SucOrder_Recursive(TNode* Ptr_Root)
/*
Walk the tree in Succ-Order
Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	if (!Ptr_Root->ltag) Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_L);
	if (!Ptr_Root->rtag) Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_R);
	//--------------
	//cout << Ptr_Root->Key_Value << ' ';
	if (!Ptr_Root->Child_L)
	{
		Ptr_Root->ltag = 1;
		Ptr_Root->Child_L = Previous;
	}
	if (!Previous->Child_R)
	{
		Previous->rtag = 1;
		Previous->Child_R = Ptr_Root;
	}
	Previous = Ptr_Root;
	//---------------
	return;
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

	TNode* Root_Ptr = NULL;
	TNode Head;
	Head.Child_L = NULL;
	Head.Child_R = NULL;
	Head.Father = NULL;
	Head.Key_Value = 0;
	Head.ltag = 0;
	Head.rtag = 0;
	Previous = &Head;
	Root_Ptr = Tree_Build_Recursive(0, 0, Element_Count);

	cout << endl << "Tree successfully build." << endl;
	cout << "Now you can choose a way you like to add thread to the tree." << endl;

	int Choice;
	cout << endl << "1.Pre-Order, Recursive" << endl;
	cout << "2.Mid-Order, Recursive" << endl;
	cout << "3.Suc-Order, Recursive" << endl;
	cout << "998.End loop" << endl;
	cout << "Your choice:";
	cin >> Choice;
	switch (Choice)
	{
	case 1:
		Tree_Walk_PreOrder_Recursive(Root_Ptr);
		Tree_Walk_PreOrder_Thread(&Head);
		cout << endl;
		break;
	case 2:
		Tree_Walk_MidOrder_Recursive(Root_Ptr);
		Tree_Walk_MidOrder_Thread(&Head);
		cout << endl;
		break;
	case 3:
		Tree_Walk_SucOrder_Recursive(Root_Ptr);
		cout << endl;
		break;
	default:
		cout << "No such choice.Please check your input." << endl;
		break;
	};



	cout << "All process is done!Excited!" << endl;

	return 0;
};