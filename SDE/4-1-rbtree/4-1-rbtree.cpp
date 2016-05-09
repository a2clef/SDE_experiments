#include <string>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <stdlib.h>


#define BLACK 1
#define RED 0

#define TEST_SIZE 15
#define MAX_NUMBER 100

using namespace std;

class bst {
private:

	struct Node {
		int value;
		bool color;
		Node *leftTree, *rightTree, *parent;

		Node() {
			color = RED;
			leftTree = NULL;
			rightTree = NULL;
			parent = NULL;
			value = 0;
		}

		Node* grandparent() {
			if (parent == NULL){
				return NULL;
			}
			return parent->parent;
		}

		Node* uncle() {
			if (grandparent() == NULL) {
				return NULL;
			}
			if (parent == grandparent()->rightTree)
				return grandparent()->leftTree;
			else
				return grandparent()->rightTree;
		}

		Node* sibling() {
			if (parent->leftTree == this)
				return parent->rightTree;
			else
				return parent->leftTree;
		}
	};

	void rotate_right(Node *p){
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->rightTree;

		fa->leftTree = y;

		if (y != NIL)
			y->parent = fa;

		p->rightTree = fa;
		fa->parent = p;

		if (root == fa)
			root = p;
		p->parent = gp;

		if (gp != NULL){
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}

	}

	void rotate_left(Node *p){
		if (p->parent == NULL){
			root = p;
			return;
		}
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->leftTree;

		fa->rightTree = y;

		if (y != NIL)
			y->parent = fa;
		p->leftTree = fa;
		fa->parent = p;

		if (root == fa)
			root = p;
		p->parent = gp;

		if (gp != NULL){
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}
	}

	void inorder(Node *p){
		if (p == NIL)
			return;

		if (p->leftTree)
			inorder(p->leftTree);

		cout << p->value << " ";

		if (p->rightTree)
			inorder(p->rightTree);
	}

	string outputColor(bool color) {
		return color ? "BLACK" : "RED";
	}

	Node* getSmallestChild(Node *p){
		if (p->leftTree == NIL)
			return p;
		return getSmallestChild(p->leftTree);
	}

	bool delete_child(Node *p, int data){
		if (p->value > data){
			if (p->leftTree == NIL){
				return false;
			}
			return delete_child(p->leftTree, data);
		}
		else if (p->value < data){
			if (p->rightTree == NIL){
				return false;
			}
			return delete_child(p->rightTree, data);
		}
		else if (p->value == data){
			if (p->rightTree == NIL){
				delete_one_child(p);
				return true;
			}
			Node *smallest = getSmallestChild(p->rightTree);
			swap(p->value, smallest->value);
			delete_one_child(smallest);

			return true;
		}
	}

	void delete_one_child(Node *p){
		Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
		if (p->parent == NULL && p->leftTree == NIL && p->rightTree == NIL){
			p = NULL;
			root = p;
			return;
		}	//there's no child, the tree is empty

		if (p->parent == NULL){
			delete  p;
			child->parent = NULL;
			root = child;
			root->color = BLACK;
			return;
		}	//have child while deleting root, make child the new root

		if (p->parent->leftTree == p){	//substitute with child
			p->parent->leftTree = child;
		}
		else {
			p->parent->rightTree = child;
		}
		child->parent = p->parent;

		if (p->color == BLACK){	//handle with a trivial case; p is red(nothing done) ; p is red and child is red
			if (child->color == RED){
				child->color = BLACK;
			}
			else
				delete_case(child); //child is the new N, turn to not trivial case
		}

		delete p;
	}

	void delete_case(Node *p){
		if (p->parent == NULL){				//CASE1: N is the new root
			p->color = BLACK;
			return;
		}

		//CASE2: p exist; S is red; => guaurantee black S and red P
		if (p->sibling()->color == RED) {
			p->parent->color = RED; //switch the color
			p->sibling()->color = BLACK;
			if (p == p->parent->leftTree)
				rotate_left(p->sibling());
			else
				rotate_right(p->sibling());
		}

		//CASE3:(parallel with case 2) S Sl Sr is black, p is black;
		if (p->parent->color == BLACK && p->sibling()->color == BLACK
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			delete_case(p->parent);
		}
		else if (p->parent->color == RED && p->sibling()->color == BLACK //CASE4: p is red, S Sl Sr is black
			&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			p->parent->color = BLACK;
		}
		else {
			//CASE5:
			if (p->sibling()->color == BLACK) {
				if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED	//Sl is red
					&& p->sibling()->rightTree->color == BLACK) {
					p->sibling()->color = RED;
					p->sibling()->leftTree->color = BLACK;
					rotate_right(p->sibling()->leftTree);
				}
				else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK	//Sr is red
					&& p->sibling()->rightTree->color == RED) {
					p->sibling()->color = RED;
					p->sibling()->rightTree->color = BLACK;
					rotate_left(p->sibling()->rightTree);
				}
			}
			//CASE6:
			p->sibling()->color = p->parent->color;
			p->parent->color = BLACK;
			if (p == p->parent->leftTree){
				p->sibling()->rightTree->color = BLACK;
				rotate_left(p->sibling());
			}
			else {
				p->sibling()->leftTree->color = BLACK;
				rotate_right(p->sibling());
			}
		}
	}

	void insert(Node *p, int data){
		if (p->value >= data){
			if (p->leftTree != NIL)	//GO left
				insert(p->leftTree, data);
			else {
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->leftTree = tmp;
				insert_case(tmp);
			}
		}
		else {						//GO right
			if (p->rightTree != NIL)
				insert(p->rightTree, data);
			else {
				Node *tmp = new Node();
				tmp->value = data;
				tmp->leftTree = tmp->rightTree = NIL;
				tmp->parent = p;
				p->rightTree = tmp;
				insert_case(tmp);
			}
		}
	}

	void insert_case(Node *p){
		if (p->parent == NULL){	//CASE1: is new root
			root = p;
			p->color = BLACK;
			return;
		}
		//CASE2 is hidden: p is black, nothing done

		//otherwise p is RED, existence of uncle is guauranteed
		if (p->parent->color == RED){
			if (p->uncle()->color == RED) { //CASE3:P U are red
				p->parent->color = p->uncle()->color = BLACK;
				p->grandparent()->color = RED;
				insert_case(p->grandparent()); //rec on G
			}
			else {
				//CASE4:
				if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {
					rotate_left(p);
					rotate_right(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {
					rotate_right(p);
					rotate_left(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				}
				else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_right(p->parent);
				}
				else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_left(p->parent);
				}
			}
		}
	}

	void DeleteTree(Node *p){
		if (!p || p == NIL){
			return;
		}
		DeleteTree(p->leftTree);
		DeleteTree(p->rightTree);
		delete p;
	}
public:

	bst() {						//The constructor
		NIL = new Node();		//NIL used ad universal NULL and leaves
		NIL->color = BLACK;
		root = NULL;
	}

	~bst() {
		if (root)
			DeleteTree(root);
		delete NIL;				//remember to free the space of NIL
	}

	void inorder() {			//walk the tree
		if (root == NULL)
			return;
		inorder(root);
		cout << endl;
	}

	void insert(int x) {
		if (root == NULL){		//trivial case: tree is empty
			root = new Node();
			root->color = BLACK;
			root->leftTree = root->rightTree = NIL;
			root->value = x;
		}
		else {
			insert(root, x);
		}
	}

	bool delete_value(int data) {
		return delete_child(root, data);
	}
private:
	Node *root, *NIL;
};





int main()
{
	srand(unsigned(time(0)));
	int randarr[TEST_SIZE];
	bst RBTree1;
	for (int i = 0; i < TEST_SIZE; i++)
	{
		randarr[i] = rand() % MAX_NUMBER;
		cout << "################################" << endl;
		cout << "Insert: " << randarr[i] << endl;
		RBTree1.insert(randarr[i]);
		RBTree1.inorder();
	};

	for (int i = 0; i < TEST_SIZE; i++)
	{
		cout << "################################" << endl;
		cout << "Remove: " << randarr[i] << endl;
		RBTree1.delete_value(randarr[i]);
		RBTree1.inorder();
	};


	return 0;
};