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
	Matrix get_rank_result(double factor)
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