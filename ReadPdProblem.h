#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#pragma warning(disable:4996)
class ReadPdProblem
{
private:
	string s_file_name;
	FILE* pf_file;
	double *pd_problem;
	int i_pd_double_size;
	void v_print_pd_table(double* pd_table, int i_size);
public:
	ReadPdProblem(string s_filename);
	~ReadPdProblem();
	void v_read_from_file();
	void v_print_pd_problem();
};

