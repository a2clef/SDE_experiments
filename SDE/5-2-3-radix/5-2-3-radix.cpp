#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define UPPER_LIMIT 1000
#define SIZE 100



int maxbit(int data[], int n) 
{
	int d = 1;
	int p = 10;
	for (int i = 0; i < n; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}
void radixsort(int data[], int n)
{
	int d = maxbit(data, n);
	int *tmp = new int[n];
	int *count = new int[10]; 
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) 
	{
		for (j = 0; j < 10; j++) count[j] = 0; 
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; //count every elelment in bucket
			count[k]++;
		}
		for (j = 1; j < 10; j++) count[j] += count[j - 1]; //process of counting sort
		for (j = n - 1; j >= 0; j--) //fit all element into the template array
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //copy it back
			data[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}

int main()
{
	srand(unsigned(time(0)));
	int arr[SIZE];
	for (int i = 0; i < SIZE; i++)
		arr[i] = rand() % UPPER_LIMIT;
	

	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << endl;

	radixsort(arr, SIZE);


	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}