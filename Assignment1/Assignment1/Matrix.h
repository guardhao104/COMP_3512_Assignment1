#pragma once
#include <iostream>

class Matrix
{
private:
	int row_number;
	int col_number;
	double **matrix;
public:
	Matrix() : row_number(0), col_number(0)
	{
		matrix = new double*[0];
		*matrix = new double[0];
	}
	Matrix(int row, int col) : row_number(row), col_number(col)
	{
		matrix = new double*[row_number];
		for (int i = 0; i < row_number; ++i)
		{
			matrix[i] = new double[col_number];
		}
	}
	Matrix(int row, int col, double num[]) : row_number(row), col_number(col)
	{
		int k = 0;
		matrix = new double*[row_number];
		for (int i = 0; i < row_number; ++i)
		{
			matrix[i] = new double[col_number];
			for (int j = 0; j < col_number; ++j)
			{
				matrix[i][j] = num[k++];
			}
		}
	}
	Matrix(const Matrix& mat) : row_number(mat.row_number), col_number(mat.col_number)
	{
		matrix = new double*[row_number];
		for (int i = 0; i < row_number; ++i)
		{
			matrix[i] = new double[col_number];
			for (int j = 0; j < col_number; ++j)
			{
				matrix[i][j] = mat.matrix[i][j];
			}
		}
	}
	~Matrix() 
	{
		for (int i = 0; i < row_number; ++i)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	Matrix& operator=(Matrix mat)
	{
		using std::swap;
		swap(row_number, mat.row_number);
		swap(col_number, mat.col_number);
		swap(matrix, mat.matrix);
		return *this;
	}
	friend Matrix operator*(Matrix mat, double factor)
	{
		for (int i = 0; i < mat.row_number; ++i)
		{
			for (int j = 0; j < mat.col_number; ++j)
			{
				mat.matrix[i][j] *= factor;
			}
		}
		return mat;
	}
	friend Matrix operator*(double factor, Matrix mat)
	{
		for (int i = 0; i < mat.row_number; ++i)
		{
			for (int j = 0; j < mat.col_number; ++j)
			{
				mat.matrix[i][j] *= factor;
			}
		}
		return mat;
	}
	friend Matrix operator*(const Matrix& m1, const Matrix& m2)
	{
		Matrix result = Matrix(m1.row_number, m2.col_number);
		for (int i = 0; i < result.row_number; ++i)
		{
			for (int j = 0; j < result.col_number; ++j)
			{
				double val = 0.0;
				for (int k = 0; k < m1.col_number; ++k)
				{
					val += m1.matrix[i][k] * m2.matrix[k][j];
				}
				result.matrix[i][j] = val;
			}
		}
		return result;
	}
	friend Matrix operator+(Matrix m1, const Matrix& m2)
	{
		for (int i = 0; i < m1.row_number; ++i)
		{
			for (int j = 0; j < m1.col_number; ++j)
			{
				m1.matrix[i][j] += m2.matrix[i][j];
			}
		}
		return m1;
	}
};