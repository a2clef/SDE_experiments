#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define MAX_COUNT 100
#define PRINT_OUTPUT 1

using namespace std;
void printArr(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		cout << arr[i] << " ";
	cout << endl;
};

void ArrRand(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		arr[i] = rand();
};

void ArrUp(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		arr[i] = i+1;
};

void ArrDown(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		arr[i] = MAX_COUNT - i;
}

void ArrSame(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		arr[i] = 998;
}


void quickSort_original(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i] < x)
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort_original(s, l, i - 1);
		quickSort_original(s, i + 1, r);
	}
}

void quickSort_randomized(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r;
		swap(s[l], s[rand() % (r - l) + l]);
		int x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i] < x)
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort_randomized(s, l, i - 1);
		quickSort_randomized(s, i + 1, r);
	}
}


void quickSort_rand_insert(int s[], int l, int r)
{
	if (l < r)
		if (r - l < 10)
		{
			for (int i = l + 1; i <= r; i++)
			{
				if (s[i - 1] > s[i])
				{
					int temp = s[i];
					int j = i;
					while (j > l && s[j - 1] > temp)
					{
						s[j] = s[j - 1];
						j--;
					}
					s[j] = temp;
				}
			}
		}
		else
		{
			int i = l, j = r;
			swap(s[l], s[rand() % (r - l) + l]);
			int x = s[l];
			while (i < j)
			{
				while (i < j && s[j] >= x)
					j--;
				if (i < j)
					s[i++] = s[j];
				while (i < j && s[i] < x)
					i++;
				if (i < j)
					s[j--] = s[i];
			}
			s[i] = x;
	
			quickSort_rand_insert(s, l, i - 1);
			quickSort_rand_insert(s, i + 1, r);
		}
}

void quickSort_rand_insert_int(int s[], int l, int r)
{
	if (l < r)
		if (r-l < 10)
		{
			for (int i = l + 1; i <= r; i++)
			{
				if (s[i - 1] > s[i])
				{
					int temp = s[i];
					int j = i;
					while (j > l && s[j - 1] > temp)
					{
						s[j] = s[j - 1];
						j--;
					}
					s[j] = temp;
				}
			}
		}
		else
		{
			int i = l, j = r;
			swap(s[l], s[rand() % (r - l) + l]);
			int x = s[l];
			while (i < j)
			{
				while (i < j && s[j] >= x)
					j--;
				if (i < j)
					s[i++] = s[j];
				while (i < j && s[i] < x)
					i++;
				if (i < j)
					s[j--] = s[i];
			}
			s[i] = x; //after here, i is the position of the pivot
			j = i;
			
			for (int k = l; k < i; k++)
			{
				if (k >= i)
					break;
				if (s[k] == x)
					swap(s[--i], s[k]);

			};

			for (int k = r; k >j ; k--)
			{
				if (k <= j)
					break;
				if (s[k] ==x)
					swap(s[++j], s[k]);

			};
			
			quickSort_rand_insert_int(s, l, i - 1);
			quickSort_rand_insert_int(s, j + 1, r);
		}
}

void sort_Test(void(*fp)(int s[], int l, int r))
{
	int arr[MAX_COUNT];

	ArrRand(arr);
	clock_t start_Time = clock();
	//=====bench start
	fp(arr, 0,MAX_COUNT-1);
	//=====bench end
	clock_t end_Time = clock();
	cout << "Rand: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	if (PRINT_OUTPUT) printArr(arr);

	ArrUp(arr);
	start_Time = clock();
	//=====bench start
	fp(arr, 0, MAX_COUNT - 1);
	//=====bench end
	end_Time = clock();
	cout << "Up: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	if (PRINT_OUTPUT) printArr(arr);



	ArrDown(arr);
	start_Time = clock();
	//=====bench start
	fp(arr, 0, MAX_COUNT - 1);
	//=====bench end
	end_Time = clock();
	cout << "Down: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	if (PRINT_OUTPUT) printArr(arr);

	ArrSame(arr);
	start_Time = clock();
	//=====bench start
	fp(arr, 0, MAX_COUNT - 1);
	//=====bench end
	end_Time = clock();
	cout << "Same: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	if (PRINT_OUTPUT) printArr(arr);



};

int main()
{
	srand(unsigned(time(0)));

	cout << "Testing Original:" << endl;
	sort_Test(quickSort_original);

	cout << endl << "Testing Randomized:" << endl;
	sort_Test(quickSort_randomized);

	cout << endl << "Testing Rand, Insert:" << endl;
	sort_Test(quickSort_rand_insert);

	cout << endl << "Testing randomized, insertion, int:" << endl;
	sort_Test(quickSort_rand_insert_int);


	return 0;
}