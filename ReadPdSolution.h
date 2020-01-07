#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#pragma warning(disable:4996)
class ReadPdSolution
{
private:
	string s_file_name;
	FILE* pf_file;
	double *pd_solution;
	int i_pd_double_size;
	void vPrintPdTable(double* pd_table, int i_size);
public:
	ReadPdSolution(string s_file_name);
	~ReadPdSolution();
	void vReadFromFile();
	void vPrintPdSolution();
	double *dGetPdSolution();
	int iGetPdDoubleSize();
};

