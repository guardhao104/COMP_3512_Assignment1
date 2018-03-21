#pragma once
#include "Matrix.h"

class PageRank
{
private:
	int page_number;
	Matrix connectivity;
public:
	PageRank() {};
	PageRank(Matrix orignal) : page_number(orignal.get_col()), connectivity(orignal) {};
	PageRank(int page, Matrix orignal) : page_number(page), connectivity(orignal) {};
	PageRank(const PageRank& src) : page_number(src.page_number), connectivity(src.connectivity) {};
	~PageRank() {};

	//This function will caculate the result of ranking.
	//PARAM		factor is describing how much the other condation will influence the final result
	//PRE		factor > 0
	//PRE		factor < 1
	//POST		NULL
	//RETURN	the result ranking matrix which has page_number row and only 1 column
	Matrix get_rank_result(double factor) const
	{
		Matrix s = make_left_stochastic_matrix();
		Matrix q = make_transition_matrix();
		Matrix m = factor * s + (1 - factor) * q;
		Matrix rank = Matrix(page_number, 1.0);
		Matrix org = rank;
		rank = m * rank;
		while (!converges(org, rank, 0.001))
		{
			org = rank;
			rank = m * rank;
		}
		rank = rank / page_number;
		return rank;
	}

	//This can give the total sum of specified column of connectivity matrix.
	//PARAM		col is the specified column
	//PRE		col >= 0
	//PRE		col < the column number of connectivity matrix
	//POST		NULL
	//RETURN	the sum of specified column
	double sum_of_col(int col) const
	{
		double sum = 0.0;
		for (int i = 0; i < connectivity.get_row(); ++i)
		{
			sum += connectivity.get_value(i, col);
		}
		return sum;
	}

	//This function can generate a left stochastic matrix from connectivity matrix.
	//PRE		NULL
	//POST		NULL
	//RETURN	left stochastic matrix
	Matrix make_left_stochastic_matrix() const
	{
		Matrix left_stochastic = connectivity;
		for (int i = 0; i < left_stochastic.get_row(); ++i)
		{
			for (int j = 0; j < left_stochastic.get_col(); ++j)
			{
				if (sum_of_col(j) != 0)
					left_stochastic.set_value(i, j,
						left_stochastic.get_value(i, j) / sum_of_col(j));
				else
					left_stochastic.set_value(i, j, 1.0 / connectivity.get_row());
			}
		}
		return left_stochastic;
	}

	//This function can generate a transition matrix from connectivity matrix.
	//PRE		NULL
	//POST		NULL
	//RETURN	transition matrix
	Matrix make_transition_matrix() const
	{
		Matrix transition = connectivity;
		for (int i = 0; i < transition.get_row(); ++i)
		{
			for (int j = 0; j < transition.get_col(); ++j)
			{
				transition.set_value(i, j, 1.0 / transition.get_row());
			}
		}
		return transition;
	}
	
	//This function is checking if two matrix have nearly value.
	//PARAM		bef and aft are both matrixes we are checking between
	//PARAM		accuracy should be the accuracy we want in checking
	//PRE		two matrixes should have same size
	//POST		NULL
	//RETURN	if two matrixes have nearly value in each position
	bool converges(const Matrix& bef, const Matrix& aft, double accuracy) const
	{
		for (int i = 0; i < bef.get_row(); ++i)
		{
			for (int j = 0; j < bef.get_col(); ++j)
			{
				double judge = bef.get_value(i, j) - aft.get_value(i, j);
				if (judge > accuracy || judge < -accuracy)
					return false;
			}
		}
		return true;
	}
};