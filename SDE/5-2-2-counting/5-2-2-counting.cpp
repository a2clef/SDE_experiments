#include <iostream>  
#include <string>  
#include <time.h>

#define SIZE  100
using namespace std;
int array[SIZE];

void count_sort(int a[], int k)
{
	int c[SIZE];
	for (int i = 0; i<k; i++)
		c[i] = 0;
	for (int i = 0; i<SIZE; i++)
		c[a[i]] ++;

	for (int i = 0; i < SIZE;i++)
		while (c[i])
		{
			cout << i << " ";
			c[i]--;
		};
	cout << endl;
}
void print_list(int array[], int length)
{
	for (int i = 0; i < length; i++)
		cout << array[i] << " ";
	cout << endl;
}
int main()
{
	srand(unsigned(time(0)));
	for (int i = 0; i<SIZE; i++)
		array[i] = rand() % SIZE;
	print_list(array, SIZE);
	count_sort(array, SIZE);
	return 0;
}
