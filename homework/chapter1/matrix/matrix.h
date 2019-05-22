#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

template<typename Object>
class matrix
{
private:
	vector< vector<Object>> array;
public:
	matrix(int rows, int cols):array(rows)
	{
		for(int i = 0; i < rows; i++)
		{
			array[i].resize(cols);
		}
	}
	
	const vector<Object> & operator[](int row)const
	{
		return array[row];
	}
	
	vector<Object> & operator[](int row)
	{
		return array[row];
	}
	
	int numrows()const
	{
		return array.size();
	}
	
	int numcols()const
	{
		return array[0].size();
	}
};

#endif




