/*Header of  Matrix class template.*/

#ifndef _MATRIX_
#define _MATRIX_
#include <iostream>
#include <vector>

/*Class derived from exception class.
operator* of Matrix class throws it then Matrices dimensions are inconsistent.*/
class InconsistentMatrixDimensions : public std::exception
{
	const char* what() const
	{
		return "Inconsistent Matrix Dimensions!";
	}
};

/*Template of Matrix class, that contains two-dimensional 
matrix with elements type equal T.*/
template <typename T>
class Matrix
{
private:
	T** arr;
	int row;
	int col;
	bool fill_check;
public:
	Matrix() {};
	Matrix(int row_a, int col_a);
	Matrix(int row_a, int col_a, T sample);
	Matrix(const Matrix& mat);
	void fill_matrix(std::vector<T> vec);
	void show_matrix();
	Matrix<T> operator*(Matrix<T> multiplier);
	~Matrix();
};

/*Template of class Matrix constructor.
The constructor recives two parametrs and reserves required memory.*/
template <typename T>
Matrix<T>::Matrix(int row_a, int col_a): row(row_a), col(col_a), fill_check(false)
{
	row = row_a;
	col = col_a;
	arr = new T*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new T[col];
	}
}

/*Template of class Matrix constructor.
The constructor recives three parametrs, reserves required memory 
and fills the memory with parameter sample.*/
template <typename T>
Matrix<T>::Matrix(int row_a, int col_a, T sample): row(row_a), col(col_a), fill_check(true)
{
	arr = new T*[row];
	for (int i = 0; i < row; i++)
	{
	arr[i] = new T[col];
	for (int j = 0; j < col; j++)
	{
	arr[i][j] = sample;
	}
	}
}

/*Copy Matrix constructor.*/
template<typename T>
Matrix<T>::Matrix(const Matrix& mat): row(mat.row), col(mat.col), fill_check(true)
{
	arr = new T*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new T[col];
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = mat.arr[i][j];
		}
	}	
}

/*Method of Matrix class, that outputs Matrix elements in console.*/
template <typename T>
void Matrix<T>::show_matrix()
{
	if (fill_check == true)
	{
		for (int i = 0; i < row; i++)
		{
			std::cout << "| ";
			for (int j = 0; j < col; j++)
			{
				std::cout << arr[i][j] << " ";
			}
			std::cout << "|";
			if (i < row - 1)
				std::cout << '\n';
		}
	}
	else
	{
		std::cout << "Fill check of Matrix didn't pass!" << '\n';
	}
}

/*Template of Matrix class Method, that fill up the object of the class.*/
template <typename T>
void Matrix<T>::fill_matrix(std::vector<T> vec)
{
	if (vec.size() > row * col)
	{
		std::cout << "Too many elements in vector" << '\n';
		return;
	}
	try
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				arr[i][j] = vec.at(i*col + j);
			}
		}
		fill_check = true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

/*Overloaded operator method, that perform multiplication of two Matrix class objects.*/
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> multiplier)
{
	if (col == multiplier.row)
	{
		Matrix<T> temp(row, multiplier.col);
		for (int k = 0; k < multiplier.col; k++)
		{
			for (int i = 0; i < row; i++)
			{
				T sum = 0;
				for (int j = 0; j < col; j++)
				{
					sum += arr[i][j] * multiplier.arr[j][k];
				}
				temp.arr[i][k] = sum;
			}
		}
		return temp;
	}
	else
	{
		throw InconsistentMatrixDimensions();
	}
}

/*Destructor of the Matrix class.*/
template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < row; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}
#endif
