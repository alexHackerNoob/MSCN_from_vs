#pragma once
using namespace std;
#include "CRandom.h"
#include <iostream> 
#define D_NO_NISTAKE 0;
#define D_MISTAKE_TABLE_PD_SOLUTION_NOT_EXIST 1; 
#define D_MISTAKE_TABLE_VALUES 2;
#define D_MISTAKE_ALREADY_EXIST_PD_PROBLEM 3; 
#define D_ANOTHER_PROBLEM 4;

#define I_ERROR_SIZE 10;
#define I_ERROR_NULL_POINTER 11;
#define I_ERROR_VALUE_INTERVAL 12;
#define I_ERROR_XD_SD_INTREVAL 13;
#define I_ERROR_XF_SF_INTREVAL 14;
#define I_ERROR_XM_SM_INTREVAL 15;
#define I_ERROR_XM_SS_INTREVAL 16;
#define I_ERROR_XD_XF_INTREVAL 17;
#define I_ERROR_XF_XM_INTREVAL 18;
#define I_NOT_SET_PD_PROBLEM 19;
#define I_NO_ERROR 20;

//const INTERVALS TO RANDOM
namespace min_max {
#define D_MAX_CD 10.0;
#define D_MAX_CF 10.0;
#define D_MAX_CM 10.0;

#define D_MAX_UD 10.0;
#define D_MAX_UF 10.0;
#define D_MAX_UM 10.0;

#define D_MAX_SD 50.0;
#define D_MAX_SF 50.0;
#define D_MAX_SM 50.0;
#define D_MAX_SS 50.0;

#define D_MIN_CD 1.0;
#define D_MIN_CF 1.0;
#define D_MIN_CM 1.0;

#define D_MIN_UD 1.0;
#define D_MIN_UF 1.0;
#define D_MIN_UM 1.0;

#define D_MIN_SD 1.0;
#define D_MIN_SF 1.0;
#define D_MIN_SM 1.0;
#define D_MIN_SS 1.0;
}
#pragma warning(disable:4996)
class CMscnProblem
{
private:
	bool *b_if_good_init;
	bool *b_if_good_pd_solution;
	bool *b_if_was_set_value;
	bool *b_if_set_pd_problem;
	bool *b_if_set_pd_solution;
	bool *b_if_set_sizes;
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

	//helpful methods
	int iGetSizeMustHave(int i_d_read_length, int i_f_read_length, int i_m_read_length, int i_s_read_length);

public:
	CMscnProblem();
	~CMscnProblem();
	bool bGetIfGoodInit();
	bool bGetIfGoodPdSolution();
	void vSetSizes(int i_d_length, int i_f_length, int i_m_length, int i_s_length);
    //need to be init
	bool ifAllExist();
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
	double dGetQuality(double *pd_solution, int i_size, double *pd_mistake);
	bool writeProblem(string s_file_name);
	bool writeSolution(string s_file_name);
	//
	bool bConstrainsSatisfied(double* pd_solution, int i_size, int *pi_error_num);
	bool bIfIntervalCorrect();
	//random_method
	void vGenerateInstance(int iInstanceSeed);

	void generateForTwoDimentional(CRandom *cR, double** pd_table, int i_line_size, int i_column_size, double i_min, double i_max);
	void generateForOneDimentional(CRandom *cR, double* pd_table, int i_size, double i_min, double i_max);

	//methods for CRandomSearch
	bool * pb_get_b_if_set_pd_problem();
	int iGetDSize();
	int iGetFSize();
	int iGetMSize();
	int iGetSSize();
	bool bIfIntervalCorrect(double* pd_solution, int i_size);
	double getDatasFromSolutionTables(double ** xd_help, double ** xf_help, double ** xm_table);
};

