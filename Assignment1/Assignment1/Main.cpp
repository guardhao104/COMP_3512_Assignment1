#include "PageRank.h"
#include <fstream>
#include <string>

#define BUFFER_SIZE 256

using namespace std;

int main()
{
	char address[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	double arr[BUFFER_SIZE * BUFFER_SIZE];
	int size = 0;
	cout << "Please enter your input file with full address path:" << endl;
	cin >> address;
	ifstream in(address);
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	in.getline(buffer, BUFFER_SIZE);
	for (int i = 0; buffer[i] == '0' || buffer[i] == '1'; i = i + 2)
	{
		size++;
		if (buffer[i] == '0')
			arr[i / 2] = 0.0;
		else 
			arr[i / 2] = 1.0;
	}
	for (int i = size; i < size * size; ++i)
	{
		in >> arr[i];
	}
	Matrix mat(size, size, arr);
	cout << "\nYour input matrix: " << endl;
	cout << mat << endl;
	PageRank pr(mat);
	Matrix rank = pr.get_rank_result(0.85);
	cout << "The ranking result: " << endl;
	for (int i = 0; i < size; ++i)
		cout << (char)('A' + i) << " = " << fixed << setprecision(3) << rank.get_value(i, 0) << endl;
	system("pause");
	return 0;
}