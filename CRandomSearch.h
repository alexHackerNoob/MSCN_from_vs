#pragma once
#include "CMscnProblem.h"
#include "CRandom.h"
using namespace std;
#include <iostream>
#define D_MIN_XD 1.0;
#define D_MAX_XD 100.0;
#define D_MIN_XF 1.0;
#define D_MAX_XF 100.0;
#define D_MIN_XM 1.0;
#define D_MAX_XM 100.0;

class CRandomSearch
{
private:
	CMscnProblem *pd_c_mscn;
	void makePdSolution(double *pd_solution, double ** xd_table, double ** xf_table, double ** xm_table, int i_d_size,int i_f_size, int i_m_size,int i_s_size);
	double *pd_best_solution;
	int i_size_solution;
	double i_profit_of_best_solution;
	void vCopyBestSolution(double* pd_solution, int i_size, int profit);
public:
	CRandomSearch(CMscnProblem * pd_c_mscn);
	~CRandomSearch();
	bool ifGetPdSolution();
	void vGenerateRandomSolution(int i_count, int i_feed);
	void printBestSolutionWithProfit();
	void vPrintArray(double **pd_table, int i_line_size, int i_column_size);
};

