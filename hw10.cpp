/***************
Lisa Chiang
Homework 10
12/05/2016
***************/

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

bool valid(int n, int x)
{
	if (x == 1)
	{
		if (n >= 1 && n <= 10)
		{
			return true;
		}
		else
		{
			cout << "That is an invalid number." << endl;
			return false;
		}
	}
	else if (x == 2)
	{
		if (n == 1 || n == 2)
		{
			return true;
		}
		else
		{
			cout << "That is an invalid option. Choose again." << endl;
			return false;
		}
	}
}

void fill_random(double table[10][10], int x, int y) 
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			table[i][j] = -10 + rand() % (21); 
		}
	}
}

void fill_matrix_from_file(ifstream &fin, double ar[10][10], int x, int y)
{ 
	int number;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			fin >> number; 
			ar[i][j] = number;
		}
	}
}

void print_matrix(double table[10][10], int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << setw(3) << table[i][j];
		}
		cout << endl; 
	}
}

void add_matrices(double table[10][10], double table2[10][10], int x, int y) 
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			table[i][j] += table2[i][j]; 
		}
	}
}

int main()
{
	srand((int)time(0)); 
	const int rows = 10; 
	const int columns = 10; 
	int num_rows, num_col;
	bool start_rows = false, start_col = false;
	int fileorrandom; 
	bool file_or_random = false; 
	double matrix_A[rows][columns]; 
	double matrix_B[rows][columns];
	string file_name; 
	int output; 
	bool output_manner = false; 
	string output_file_name; 

	//getting number of rows
	while (!start_rows)
	{
		cout << "Please insert how many rows you want (number must be between 1 and 10): ";
		cin >> num_rows;

		start_rows = valid(num_rows, 1); 
	}
	//getting number of columns
	while (!start_col)
	{
		cout << "Please insert how many columns you want (number must be between 1 and 10): ";
		cin >> num_col;
		
		start_col = valid(num_col, 1);
	}

	cout << endl << "Please choose from the following (Enter a number): " << endl; 
	cout << "  1 Fill the matrices from a file." << endl; 
	cout << "  2 Fill the matrices with random values." << endl << endl; 

	//choosing an option - file or random numbers
	while (!file_or_random)
	{
		cin >> fileorrandom;
		file_or_random = valid(fileorrandom, 2);
	}
	
	//file
	if (fileorrandom == 1)
	{
		cout << "Enter a file name: ";
		cin >> file_name;

		//file or console
		while (!output_manner)
		{
			cout << "Would you like the output to go to (Enter a number): \n  1 File\n  2 Console" << endl;
			cin >> output;

			output_manner = valid(output, 2);
		}

		//opening file
		ifstream fin;
		fin.open(file_name.c_str());

		//filling matrices A, B
		fill_matrix_from_file(fin, matrix_A, num_rows, num_col);
		fill_matrix_from_file(fin, matrix_B, num_rows, num_col);

		//close file 
		fin.close();

		//file
		if (output == 1)
		{
			cout << "Choose an output file name: ";
			cin >> output_file_name;

			//open output file
			ofstream fout;
			fout.open(output_file_name.c_str(), ios::app);

			//put matrix A into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_A[i][j];
					fout << number;
					fout << " "; 
				}
				fout << endl;
			}
			
			//put matrix B into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_B[i][j];
					fout << number;
					fout << " "; 
				}
				fout << endl;
			}

			//adding matrices
			add_matrices(matrix_A, matrix_B, num_rows, num_col);

			//put added matrix A (addition of A + B) into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_A[i][j];
					fout << number;
					fout << " "; 
				}
				fout << endl;
			}

			//close output file
			fout.close();
		}

		//console 
		if (output == 2)
		{
			print_matrix(matrix_A, num_rows, num_col);
			cout << endl; 
			print_matrix(matrix_B, num_rows, num_col); 
			cout << endl; 

			//adding matrices
			add_matrices(matrix_A, matrix_B, num_rows, num_col);

			//matrix a is now equal to A + B (since overwritten in adding file)
			print_matrix(matrix_A, num_rows, num_col);
		}
	}
	
	//random numbers
	if (fileorrandom == 2)
	{
		fill_random(matrix_A, num_rows, num_col);
		fill_random(matrix_B, num_rows, num_col);
		
		//1 file or 2 console
		while (!output_manner)
		{
			cout << "Would you like the output to go to (Enter a number): \n  1 File\n  2 Console" << endl;
			cin >> output;

			output_manner = valid(output, 2);
		}

		if (output == 1)
		{
			cout << "Choose an output file name: ";
			cin >> output_file_name;

			//open output file
			ofstream fout;
			fout.open(output_file_name.c_str(), ios::app);

			//put matrix A into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_A[i][j];
					fout << number;
					fout << " "; 
				}
				fout << endl;
			}

			//put matrix B into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_B[i][j];
					fout << number;
					fout << " ";
				}
				fout << endl;
			}

			//adding matrices
			add_matrices(matrix_A, matrix_B, num_rows, num_col);

			//put added matrix A (addition of A + B) into output file
			for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < num_col; j++)
				{
					double number = matrix_A[i][j];
					fout << number;
					fout << " ";
				}
				fout << endl;
			}

			//close output file
			fout.close();
		}

		if (output == 2)
		{
			print_matrix(matrix_A, num_rows, num_col);
			cout << endl; 
			print_matrix(matrix_B, num_rows, num_col);
			cout << endl; 

			//adding matrices
			add_matrices(matrix_A, matrix_B, num_rows, num_col);

			//matrix a is now equal to A + B (since overwritten in adding file)
			print_matrix(matrix_A, num_rows, num_col);
		}
	}

	system("pause");
	return 0;
}