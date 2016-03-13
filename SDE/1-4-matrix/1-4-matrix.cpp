#include <iostream>
#include <vector>

class _tuple
{
public:
	friend class Matrix_tuple;
private:
	int x, y, value;
};

class  Matrix_tuple
{
public:
	Matrix_tuple()
	{
		m = 0;
		n = 0;
	};

	~Matrix_tuple()
	{
		vec.clear();
	};

	void matrix_read()
	{
		using namespace std;
		cout << "Please input m and n." << endl;
		cin >> m >> n;
		cout << "Please input count." << endl;
		int count;

		_tuple temp_tuple;
		cin >> count;
	
		cout << "Please input x,y,value." << endl;
		while (count)
		{
			cin >> temp_tuple.x >> temp_tuple.y >> temp_tuple.value;
			if (temp_tuple.value)
				vec.push_back(temp_tuple);
			count--;
		};


	};

	void matrix_transpose_naive()
	/*
	this is not a in-place transepose.
	although complicity is linear,its not efficient

	just an instance of fast transpose
	*/
	{
		using namespace std;
		int element_count = vec.size();
		//vector<int> line_position;
		vector<_tuple> temp_vec;
		int temp;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < element_count; j++)
			{
				if (vec[j].y - 1 == i)
				{
					temp_vec.push_back(vec[j]);
					temp = temp_vec[temp_vec.size() - 1].x;
					temp_vec[temp_vec.size() - 1].x = temp_vec[temp_vec.size() - 1].y;
					temp_vec[temp_vec.size() - 1].y = temp;
				};
			};
		temp = m;
		m = n;
		n = temp;
		vec.clear();
		for (int i = 0; i < element_count; i++)
			vec.push_back(temp_vec[i]);

		cout << "Transpose operation ended successfully." << endl;
		return;
	};

	void matrix_write()
	{
		using namespace std;
		cout << "This is a " << m << " * " << n << " matrix." << endl;
		int position = 0;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				if (vec[position].x == i + 1 && vec[position].y == j + 1)
				{
					cout << vec[position].value << " ";
					position++;
				}
				else
					cout << "0 ";
			cout << endl;
		};
	};

private:
	std::vector<_tuple> vec;
	int m, n;


};




int main()
{
	using namespace std;
	while (1)
	{
		Matrix_tuple test_matrix;
		test_matrix.matrix_read();
		test_matrix.matrix_write();
		test_matrix.matrix_transpose_naive();
		test_matrix.matrix_write();
	};



	return 0;
};