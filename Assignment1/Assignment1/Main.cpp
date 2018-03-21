#include "PageRank.h"
#include <fstream>
#include <string>

#define BUFFER_SIZE 256

using namespace std;

//The input method that get a matrix from a text file. 
//User can type the address of file to input.
//PARAM		size is the number that matrix row and column, otherwise, the number of webpages
//PARAM		arr[] is the array we record the int data from file
//PRE		size should start from 0
//PRE		arr[] should have enough size
//POST		size will become specified number by counting data in file
//POST		arr[] will record all data in file
//RETURN	if the input operation sucessful
bool get_input_matrix_file(int *size, double arr[])
{
	char address[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	cout << "Please enter your input file with full address path:" << endl;
	cin >> address;
	ifstream in(address);
	if (!in.is_open())
	{
		cout << "Error opening file";
		return false;
	}
	in.getline(buffer, BUFFER_SIZE);
	for (int i = 0; buffer[i] == '0' || buffer[i] == '1'; i = i + 2)
	{
		++*size;
		if (buffer[i] == '0')
			arr[i / 2] = 0.0;
		else
			arr[i / 2] = 1.0;
	}
	for (int i = *size; i < *size * *size; ++i)
	{
		in >> arr[i];
	}
	return true;
}

//The output method that generate a file named PageRank.txt to record the ranking result.
//PARAM		size is the number of webpages
//PARAM		rank is the ranking matrix
//PRE		size should match the row number of rank matrix
//POST		a file named PageRank.txt wil be generated
//RETURN	if the output operation sucessful
bool generate_output_ranking_file(int size, const Matrix& rank)
{
	ofstream out("PageRank.txt");
	if (out.is_open())
	{
		for (int i = 0; i < size; ++i)
			out << (char)('A' + i) << " = " << fixed << setprecision(3) << rank.get_value(i, 0) << endl;
		out.close();
		return true;
	}
	return false;
}

int main()
{
	//Part A: input
	double arr[BUFFER_SIZE * BUFFER_SIZE];
	int size = 0;
	if (!get_input_matrix_file(&size, arr))
	{
		system("pause");
		return 0;
	}

	//Part B: calculate
	Matrix mat(size, size, arr);
	cout << "\nYour input matrix: " << endl;
	cout << mat << endl;
	PageRank pr(mat);
	Matrix rank = pr.get_rank_result(0.85);
	cout << "The ranking result: " << endl;
	for (int i = 0; i < size; ++i)
		cout << (char)('A' + i) << " = " << fixed << setprecision(3) << rank.get_value(i, 0) << endl;

	//Part C: output
	if (generate_output_ranking_file(size, rank))
	{
		cout << "\nA file named PageRank.txt has been generated with this result!\n" << endl;
	}

	system("pause");
	return 0;
}