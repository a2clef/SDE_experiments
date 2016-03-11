#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <limits.h>

#define random(x) (rand()%x)

//written by aclef 20160311

/*
	this a instance of skiplist data structure
	created with templates, so all data type can be compared with < > =
	can be used as the element.
	remember to overload these operator.

	

	this simple, efficient and elegant masterpiece is created by william pugh in the last century
	This instance maybe little different from the original paper, but they'll definite do the work
	(because the original code is written in english and i didnt read the whole paper)
*/

//#ifndef 

//#define __HEADER_SKIPLIST

#define DEFAULT_EXPECTED_HEIGHT 2

template <class T>
class skiplist_node
{
public:
	T element_value;

	skiplist_node<T>* pointer_next_element;
	skiplist_node<T>* pointer_next_layer;

	skiplist_node()				//the default constructor of the node
	{
		next_element = NULL;
		next_layer = NULL;
	};

	skiplist_node(T element_init)	//can also create a element initialized
	{
		pointer_next_element = NULL;
		pointer_next_layer = NULL;
		element_value = element_init;

	};

	skiplist_node(T* pointer_element_init)
		//and can create a element with a pointer
	{
		pointer_next_element = NULL;
		pointer_next_layer = NULL;
		element_value = *pointer_element_init;
	};
};


template <class T>
class skiplist
{
public:
	void sl_insert(T element_insert)	//add a element to the list 
	{
		skiplist_node<T>* ptr_temp_level = pointer_head;
		skiplist_node<T>* ptr_temp_node_prev=NULL;
		skiplist_node<T>* ptr_temp_node_now;
		skiplist_node<T>* ptr_temp_node_new;
		int height_instance = random_height();
		for (int i = 0; i < expected_height * 2 - 1 - height_instance; i++)
			ptr_temp_level = ptr_temp_level->pointer_next_layer;
		while (ptr_temp_level)
		{
			ptr_temp_node_now = ptr_temp_level;
			if (ptr_temp_node_now->pointer_next_element)
				while (ptr_temp_node_now->pointer_next_element->element_value < element_insert)
				{
					ptr_temp_node_now = ptr_temp_node_now->pointer_next_element;
					if (!ptr_temp_node_now->pointer_next_element)
						break;
				};
			ptr_temp_node_new = new skiplist_node<T>(element_insert);

			ptr_temp_node_new->pointer_next_element = ptr_temp_node_now->pointer_next_element;
			ptr_temp_node_now->pointer_next_element = ptr_temp_node_new;


			if (ptr_temp_node_prev)
				ptr_temp_node_prev->pointer_next_layer = ptr_temp_node_now->pointer_next_element;
			ptr_temp_node_prev = ptr_temp_node_now->pointer_next_element;

			ptr_temp_level = ptr_temp_level->pointer_next_layer;
		};
	};
	int sl_search(T element_search)		//if exist, return 1
	{
		skiplist_node<T>* pointer_temp_node=pointer_head;
		while (1)
		{
			while (pointer_temp_node->pointer_next_element && (pointer_temp_node->pointer_next_element->element_value <= element_search))
				pointer_temp_node = pointer_temp_node->pointer_next_element;
			if (pointer_temp_node->pointer_next_layer)
			{
				pointer_temp_node = pointer_temp_node->pointer_next_layer;
			}
			else if (pointer_temp_node->element_value == element_search)
				return 1;
			else
				return 0;
			//---------------------------------------
			/*if (pointer_temp_node->pointer_next_element && pointer_temp_node->pointer_next_element->element_value > element_search)
			{
				pointer_temp_node = pointer_temp_node->pointer_next_element;
				continue;
			};
			if (pointer_temp_node->element_value == element_search)
			{
				return 1;
			};
			if (pointer_temp_node->pointer_next_layer)
				pointer_temp_node = pointer_temp_node->pointer_next_layer;
			else
				return 0;*/
		};
	};
	void sl_delete(T element_delete)	//delete a element from the list
	{
		if (!sl_search(element_delete))
		{
			std::cout << "element not found.please check" << std::endl;
			return;
		};
		skiplist_node<T>* ptr_node_layer = pointer_head;
		skiplist_node<T>* ptr_node_now;
		skiplist_node<T>* ptr_node_del;
		while (1)
		{
			ptr_node_now = ptr_node_layer;

			while (ptr_node_now->pointer_next_element)
			{
				if (ptr_node_now->pointer_next_element->element_value == element_delete)
				{
					ptr_node_del = ptr_node_now->pointer_next_element;
					ptr_node_now->pointer_next_element = ptr_node_del->pointer_next_element;
					delete ptr_node_del;
					break;
				}; 
				ptr_node_now = ptr_node_now->pointer_next_element;
			};

			if (ptr_node_layer->pointer_next_layer)
				ptr_node_layer = ptr_node_layer->pointer_next_layer;
			else
				break;
		};
	};

	void sl_list()
	{
		skiplist_node<T>* ptr_node_layer = pointer_head;
		while (ptr_node_layer->pointer_next_layer)
			ptr_node_layer = ptr_node_layer->pointer_next_layer;
		while (ptr_node_layer->pointer_next_element)
		{
			std::cout << ptr_node_layer->pointer_next_element->element_value << " ";
			ptr_node_layer = ptr_node_layer->pointer_next_element;
		};
		std::cout << std::endl;
		return;
	};

	skiplist<T>(int height)				//constructor with specific height
	{
		pointer_head = NULL;
		element_count = 0;
		expected_height = height;
		skiplist_build();
	};

	~skiplist()
	/*
		the destructor
		free all memory used by the structure

	*/
	{
		skiplist_node<T>* ptr_node_now;
		skiplist_node<T>* ptr_node_del;
		skiplist_node<T>* ptr_level = pointer_head;
		while (ptr_level)
		{
			ptr_node_del = ptr_level;
			ptr_level = ptr_level->pointer_next_layer;
			ptr_node_now = ptr_node_del->pointer_next_element;
			while (ptr_node_del)
			{
				delete ptr_node_del;
				ptr_node_del = ptr_node_now;
				if (!ptr_node_del) break;
				ptr_node_now = ptr_node_now->pointer_next_element;
			};
		}
		return;
	};


private:
	int element_count;					//metadata
	int expected_height;

	skiplist_node<T>* pointer_head;					//the pointer of the head
	/*
	this pointer pointers to a link list, collects all head of every layer.
	*/

	void skiplist_build()
	/*
		after we know the expected height of the skiplist, we can build the skeleton of the skiplist;
		expand every layer of the skiplist;
	*/
	{
		pointer_head = new skiplist_node<T>(INT_MIN);
		/*
			there's no element in the list, head is connected to the tail.
		*/

		srand((int)time(0));		//random number seed, for later use

		skiplist_node<T>* pointer_temp_node = pointer_head;
		for (int i = 1; i < expected_height * 2;i++)
		{
			pointer_temp_node->pointer_next_layer = new skiplist_node<T>(INT_MIN);
			pointer_temp_node = pointer_temp_node->pointer_next_layer;
		};
	};

	inline int random_height()
	/*
		this is function built in a linklist node
		returns ramdom number with expectaion of expected_height
	*/
	{
		//return ramdom(expected_height * 2);
		return rand() % (expected_height*2);
	};

	skiplist()						//the default constructor, initialize the list
	{
		pointer_head = NULL;
		element_count = 0;
		expected_height = DEFAULT_EXPECTED_HEIGHT;
		skiplist_build();
	};
	
};



//#endif



int main()
{
	using namespace std;
	cout << "This is a program to test the function of a skip list." << endl;
	int chosen_height;

	cout << "Please input the estimated height of the skiplist." << endl;
	cout << "The default is 2.Please input a integer between [1,1000]." << endl;
	cout << "The bigger, the faster, and more space consumption." << endl;
	cin >> chosen_height;
	if (chosen_height < 1 || chosen_height > 1000)
	{
		cout << "Illigal input, set to default." << endl;
		chosen_height = DEFAULT_EXPECTED_HEIGHT;
	};

	skiplist<int> skiplist_instance_test(chosen_height);
	string command;
	int element_input;

	cout << "A skiplist is created, please input your action" << endl;
	while (1)
	{
		cin >> command;
		if (command == "insert")
		{
			cin >> element_input;
			skiplist_instance_test.sl_insert(element_input);
			continue;
		};
		if (command == "delete")
		{
			cin >> element_input;
			skiplist_instance_test.sl_delete(element_input);
			continue;
		};
		if (command == "list")
		{
			skiplist_instance_test.sl_list();
			continue;
		}
		if (command == "search")
		{
			cin >> element_input;
			if (skiplist_instance_test.sl_search(element_input))
				cout << "This element is in the list" << endl;
			else
				cout << "This element is not in the list" << endl;
			continue;
		};
		if (command == "exit")
			break;
		cout << "wrong input, please check." << endl;
	};

	return 0;
};