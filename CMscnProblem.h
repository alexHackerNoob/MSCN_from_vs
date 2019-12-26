#pragma once
using namespace std;
#include <iostream>
class CMscnProblem
{
private:
	bool *b_if_good_init;
	bool *b_if_good_pd_solution;
	bool *b_if_was_set_value;
	bool *b_if_set_pd_problem;
	//cena dostawki + przerabienia
	double **cd_table = NULL;
	double **cf_table = NULL;
	double **cm_table = NULL;
	//moc produzyjna
	double *sd_table = NULL;
	double *sf_table = NULL;
	double *sm_table = NULL;
	double *ss_table = NULL;
	//tablicy jendorazowego kosztu
	double *ud_table;
	double *uf_table;
	double *um_table;
	//zyski
	double *p_table;

	//zakresy wartosci

	std::pair<double, double>** xd_min_max;
	std::pair<double, double>** xf_min_max;
	std::pair<double, double>** xm_min_max;

	//parametrs of solution
	double **xd_table;
	double **xf_table;
	double **xm_table;
	//size of elements
	int i_d_size;
	int i_f_size;
	int i_m_size;
	int i_s_size;

	//delete methods
	void vDeleteOneDimensionalArray(double* pd_table);
	void vDeleteTwoDementionalArray(double** pd_table, int i_size);
	void vDeleteTwoDementionalArray(std::pair<double, double>** pp_pointer ,int i_size);

	//printMethods
	void vPrintBoolPointer(bool* pb_pointer);
	void vPrintOneDemensionalArray(double* pd_table, int i_size);
	void vPrintTwoDementionalArray(double** pd_table, int i_line_size, int i_column_size);
	void vPrintTwoDementionalArray(std::pair<double, double>** pp_pointer, int i_line_size, int i_column_size);
public:
	CMscnProblem();
	~CMscnProblem();
	bool bGetIfGoodInit();
	bool bGetIfGoodPdSolution();
	void vSetSizes(int i_d_length, int i_f_length, int i_m_length, int i_s_length);
	//setValue methods
	//two-dementional tables
	bool bsetValueCD(double d_value, int i_x_index, int i_y_index);
	bool bsetValueCF(double d_value, int i_x_index, int i_y_index);
	bool bsetValueCM(double d_value, int i_x_index, int i_y_index);
	//one-dementional tables
	bool bsetValueSD(double d_value, int i_index);
	bool bsetValueSF(double d_value, int i_index);
	bool bsetValueSM(double d_value, int i_index);
	bool bsetValueSS(double d_value, int i_index);
	//get datas from pd_table
	bool bGetDatasFromProblem(double* pd_problem, int i_size);
	bool bGetDatasFromSolution(double* pd_solution, int i_size);
	void vPrintAllDatas();
};

