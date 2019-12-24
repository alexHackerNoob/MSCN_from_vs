#pragma once
using namespace std;
#include <iostream>
class CMscnProblem
{
private:
	bool *b_if_good_init;
	bool *b_if_good_pd_solution;
	bool *b_if_was_set_value;
	//cena dostawki + przerabienia
	double **cd_table = NULL;
	double **cf_table = NULL;
	double **cm_table = NULL;
	//moc produzyjna
	double *sd_table = NULL;
	double *sf_table = NULL;
	double *sm_table = NULL;
	double *ss_table = NULL;
	//size of elements
	int i_d_size;
	int i_f_size;
	int i_m_size;
	int i_s_size;

	//delete methods
	void vDeleteOneDimensionalArray(double* pd_table);
	void vDeleteTwoDementionalArray(double** pd_table, int i_size);
public:
	CMscnProblem();
	~CMscnProblem();
	bool bGetIfGoodInit();
	bool bGetIfGoodPdSolution();
	void vSetSizes(int i_d_length, int i_f_length, int i_m_length, int i_s_length);
	//setValue methods
	//two-dementional tables
	bool setValueCD(double d_value, int i_x_index, int i_y_index);
	bool setValueCF(double d_value, int i_x_index, int i_y_index);
	bool setValueCM(double d_value, int i_x_index, int i_y_index);
	//one-dementional tables
	bool setValueSD(double d_value, int i_index);
	bool setValueSF(double d_value, int i_index);
	bool setValueSM(double d_value, int i_index);
	bool setValueSS(double d_value, int i_index);
};

