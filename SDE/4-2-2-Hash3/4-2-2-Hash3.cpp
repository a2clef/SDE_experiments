#include <iostream>
#include <time.h>
#include <stdlib.h>
/*
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191
193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283
293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401
409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509
521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631
641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751
757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877
881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 1009
1013 1019 1021 1031 1033 1039 1049 1051 1061 1063 1069 1087 1091 1093 1097
1103 1109 1117 1123 1129 1151 1153 1163 1171 1181 1187 1193 1201 1213 1217
1223 1229 1231 1237 1249 1259 1277 1279 1283

*/
using namespace std;

#define MAX_COUNT 151
#define MAX_COLLISION 150
#define TEST_SIZE 152

int table[MAX_COUNT];
bool used[MAX_COUNT];
bool full[MAX_COUNT];
int elementCount = 0;

int hash1(int key)
{
	int temp=key;
	int result=0;
	while (temp)
	{
		result += temp%MAX_COUNT;
		temp /= MAX_COUNT;
	};
	return result % MAX_COUNT;
};

int insert(int key)
{
	int Collision = 0;
	int pos = hash1(key);
	while (full[pos])
	{
		pos++;
		pos %= MAX_COUNT;
		Collision++;
		if (Collision > MAX_COLLISION)
		{
			cout << "Insert " << key << " Failed: Collision exceed" << endl;
			return -1;
		};
	};
	table[pos] = key;
	used[pos] = 1;
	full[pos] = 1;
	elementCount++;
	cout << "Insert " << key << " Successful " << Collision << endl;
	return Collision;
};

int remove(int key)
{
	int Collision = 0;
	int pos = hash1(key);
	while (1)
	{
		if (!used[pos])
		{
			cout << "Remove: " << key << " FAILED: NOT FOUND" << endl;
			return -1;
		};
		if (table[pos] == key && full[pos])
		{
			//-----------
			cout << "Remove:" << table[pos] << " Successfully " << Collision << endl;
			//-----------
			full[pos] = 0;
			elementCount--;
			return Collision;
		};
		//pos = hash1(pos);
		pos++;
		pos %= MAX_COUNT;
		Collision++;
		if (Collision > MAX_COLLISION)
		{
			cout << "Remove: " << key << " FAILED: NOT FOUND" << endl;
			return -1;
		}
	};
};

bool find(int key)
{
	int pos = hash1(key);
	int Collision = 0;
	while (1)
	{
		if (!used[pos])
			return false;
		if (table[pos] == key)
			if (full[pos])
				return true;
		pos++;
		pos %= MAX_COUNT;
		Collision++;
		if (Collision > MAX_COLLISION)
			return false;
	};
};
int main()
{
	srand(unsigned(time(0)));
	memset(used, 0, sizeof(bool)*MAX_COUNT);
	memset(full, 0, sizeof(bool)*MAX_COUNT);

	int randarr[TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++)
	{
		randarr[i] = rand();
		insert(randarr[i]);
	};
	cout << "##############################################" << endl;
	for (int i = 0; i < TEST_SIZE / 2; i++)
		remove(randarr[rand() % TEST_SIZE]);
	cout << "##############################################" << endl;
	for (int i = 0; i < TEST_SIZE / 2; i++)
	{
		int pk = randarr[rand() % TEST_SIZE];
		if (find(pk))
			cout << "Exists:" << pk << endl;
		else
			cout << "Not EXIST:" << pk << endl;
	};

	return 0;
};