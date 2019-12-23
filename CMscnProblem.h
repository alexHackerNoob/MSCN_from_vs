#pragma once
using namespace std;
#include <iostream>
class CMscnProblem
{
private:
	bool * b_if_good_init = new bool;
	bool * b_if_good_set_value = new bool;
	bool * b_if_good_pd_solution = new bool;
	//cena dostawki + przerabienia
	double **cd_table = nullptr;
	double **cf_table = nullptr;
	double **cm_table = nullptr;
	//moc produzyjna
	double *sd_table = nullptr;
	double *sf_table = nullptr;
	double *sm_table = nullptr;
	double *ss_table = nullptr;
	//size of elements
	int d_size = 0;
	int f_size = 0;
	int m_size = 0;
	int s_size = 0;
	//set sizes
	void vSetSizeOfD(int d_size);
	void vSetSizeOfF(int f_size);
	void vSetSizeOfM(int m_size);
	void vSetSizeOfS(int s_size);
	//delete methods
	void vDeleteOneDimensionalArray(double* pd_table);
	void vDeleteTwoDementionalArray(double** pd_table, int i_size);
	//copy and return new size
	int vCopyTableOneD(int i_prev_size, int i_future_size, double* pd_table);
	int vCopyTableTwoD(int i_prev_size, int i_future_size, double** pd_table);
public:
	CMscnProblem();
	~CMscnProblem();
	bool getIfGoodInit();
	bool getbIfGoodSetValue();
	bool getGoodPdSolution();
	void setSizes(int d_size, int f_size, int m_size, int s_size);
	void setSizesSmart(int d_size, int f_size, int m_size, int s_size);
	void vSetSmartSizeCd(int d_size, int f_size);
    void vSetSmartSizeCf(int f_size, int m_size);
	void vSetSmartSizeCm(int m_size, int s_size);
	void setValueOfCD(int i_index1,int i_index2, double value);
	void setValueOfCF(int i_index1, int i_index2, double value);
	void setValueOfCM(int i_index1, int i_index2, double value);
	bool vGetQuality(double *pd_solution, int i_size_pd_solution);
};

