#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

#define UPPER_LIMIT 10000
#define BUCKET_NUMBER 10
#define TEST_SIZE 100

using namespace std;
vector<int> buckets[BUCKET_NUMBER];

int main()
{
	srand(unsigned(time(0)));
	int arr[TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++)
		arr[i] = rand() % UPPER_LIMIT;

	for (int i = 0; i < TEST_SIZE; i++)
		buckets[arr[i] / 1000].push_back(arr[i]);

	for (int i = 0; i < BUCKET_NUMBER; i++)
	{
		sort(buckets[i].begin(), buckets[i].end());
		for (unsigned int j = 0; j < buckets[i].size(); j++)
			cout << buckets[i][j] << " ";
		cout << endl;
	};
	return 0;
}