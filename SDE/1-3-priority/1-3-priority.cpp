#include <iostream>
#include <vector>
#include <string>

template <class T>
class p_queue
{
public:
	void enqueue(T &item)
	{
		vec.push_back(item);		//add the new element into the tail of the list
		int position = vec.size() - 1;
		while ((position > 1) && (vec[position] < vec[position / 2]))
		{
			element_swap(vec[position], vec[position / 2]);
			position /= 2;
		};
		return;
	};
	T peek_element()						//in case of unexpected assignment, not using reference
	{
		return vec[1];
	};
	void peek_display()
	{
		using namespace std;
		if (vec.size() <= 1)
		{
			cout << "The queue is empty." << endl;
			return;
		};
		cout << peek_element() << endl;
		return;
	};
	void dequeue()
	{
		using namespace std;
		//if dont want any info while dequeue, quote the line below

		if (vec.size() == 1)
		{
			cout << "The queue is already empty, please check" << endl;
			return;
		};

		cout << "The element dequeued is " << vec[1] << endl;
		element_swap(vec[1], vec[vec.size()-1]);
		vec.pop_back();			//remove the element from the list
		
		unsigned int position=1;
		while (position * 2 < vec.size())						//maintain the properity of the heap
			if ((position * 2 + 1) == vec.size())					//in this case, the point only have left child
			{
				if (vec[position] > vec[position * 2])
					swap(vec[position], vec[position * 2]);
				break;
			}
			else if (vec[position * 2] < vec[position] || vec[position * 2 + 1] < vec[position])					//otherwise, the point have 2 child
			{
				if (vec[position * 2] < vec[position * 2 + 1])			//left child is smaller than right child
				{
					element_swap(vec[position], vec[position * 2]);
					position *= 2;
				}
				else													//otherwise, the right child is smaller	
				{
					element_swap(vec[position], vec[position * 2 + 1]);
					position = position * 2 + 1;
				};
			}
			else break;			//already fits the profile of a heap, exit

		return;
	};

	int element_count()
	{
		return vec.size() - 1;
	};

	p_queue()					//default constructor
	{
		T nullelement;			//elements in heap starts with 1
		vec.push_back(nullelement);
	};

	~p_queue()					//default destructor
	{
		vec.clear();
	};
private:
	std::vector<T> vec;			//an vector that stores all content


	void element_swap(T &a, T &b)
	{
		T element_temp = a;
		a = b;
		b = element_temp;
		return;
	};

};




int main()
{
	using namespace std;

	p_queue<int> queue_test;
	string command;
	
	cout << "This is a test prog of priority queue.Please input your command." << endl;

	while (1)
	{
		cin >> command;
		if (command == "en")
		{
			int input;
			cin >> input;
			queue_test.enqueue(input);
			continue;
		};
		if (command == "de")
		{
			queue_test.dequeue();
			continue;
		};
		if (command == "peek")
		{
			queue_test.peek_display();
			continue;
		};
		if (command == "count")
		{
			cout << queue_test.element_count() << endl;
			continue;
		};
		if (command == "exit")
			break;

		cout << "This command doesnt exist, please check." << endl;
	
	};


	return 0;
}