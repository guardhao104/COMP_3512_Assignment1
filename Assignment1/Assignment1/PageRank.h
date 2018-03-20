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
		Matrix s = connectivity.make_left_stochastic_matrix();
		Matrix q = connectivity.make_transition_matrix();
		Matrix m = factor * s + (1 - factor) * q;
		Matrix rank = Matrix(page_number, 1.0);
		Matrix org = rank;
		rank = m * rank;
		while (!rank.converges(org))
		{
			org = rank;
			rank = m * rank;
		}
		rank = rank / page_number;
		return rank;
	}

};