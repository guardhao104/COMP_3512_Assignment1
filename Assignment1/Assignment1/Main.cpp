#include "PageRank.h"

using namespace std;

int main()
{
	double arr[] = { 0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0 };
	Matrix mat(4, 4, arr);
	cout << "Test matrix: " << endl;
	cout << mat << endl;
	PageRank pr(mat);
	Matrix rank = pr.get_rank_result(0.85);
	cout << "Ranking matrix: " << endl;
	cout << rank << endl;
	system("pause");
	return 0;
}