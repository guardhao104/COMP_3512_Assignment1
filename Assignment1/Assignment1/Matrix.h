#pragma once
#include <iostream>
#include <iomanip>

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
	Matrix(int row, double num) : row_number(row), col_number(1)
	{
		matrix = new double*[row_number];
		for (int i = 0; i < row_number; ++i)
		{
			matrix[i] = new double[col_number];
			for (int j = 0; j < col_number; ++j)
			{
				matrix[i][j] = num;
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
	void set_row(int row) { row_number = row; };
	int get_row() const { return row_number; };
	void set_col(int col) { col_number = col; };
	int get_col() const { return col_number; };
	void set_value(int row, int col, double val) { matrix[row][col] = val; };
	double get_value(int row, int col) const { return matrix[row][col]; };

	//Overload operator = for assignment.
	Matrix& operator=(Matrix mat)
	{
		using std::swap;
		swap(row_number, mat.row_number);
		swap(col_number, mat.col_number);
		swap(matrix, mat.matrix);
		return *this;
	}

	//Overload operator * between matrix and number.
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

	//Overload operator * between matrix and number.
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

	//Overload the operator * between two matrix that the first one has
	//the same colunm number as the row number of second matrix.
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

	//Overload the operator / between a matrix and a number.
	friend Matrix operator/(Matrix mat, double factor)
	{
		for (int i = 0; i < mat.row_number; ++i)
		{
			for (int j = 0; j < mat.col_number; ++j)
			{
				mat.matrix[i][j] /= factor;
			}
		}
		return mat;
	}

	//Overload the operator + between two matrix in same size.
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

	//Overload the operator << to print a matrix.
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat)
	{
		for (int i = 0; i < mat.row_number; ++i)
		{
			for (int j = 0; j < mat.col_number; ++j)
				out << std::setw(2) << mat.matrix[i][j] << "  ";
			out << std::endl;
		}
		return out;
	}
};