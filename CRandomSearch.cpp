#include "CRandomSearch.h"







void CRandomSearch::makePdSolution(double * pd_solution, double ** xd_table, double ** xf_table, double ** xm_table, int i_d_size, int i_f_size, int i_m_size, int i_s_size)
{
	int i_current_index = 0;
	pd_solution[i_current_index++] = i_d_size;
	pd_solution[i_current_index++] = i_f_size;
	pd_solution[i_current_index++] = i_m_size;
	pd_solution[i_current_index++] = i_s_size;
	for (int i = 0; i < i_d_size; i++)
	{
		for (int j = 0; j < i_f_size; j++)
		{
			pd_solution[i_current_index++] = xd_table[i][j];
		}
	}
	for (int i = 0; i < i_f_size; i++)
	{
		for (int j = 0; j < i_m_size; j++)
		{
			pd_solution[i_current_index++] = xf_table[i][j];
		}
	}
	for (int i = 0; i < i_m_size; i++)
	{
		for (int j = 0; j < i_s_size; j++)
		{
			pd_solution[i_current_index++] = xm_table[i][j];
		}
	}
}

void CRandomSearch::vCopyBestSolution(double* pd_solution, int i_size, int profit)
{
	if (this->pd_best_solution != NULL) delete this->pd_best_solution;
	this->pd_best_solution = new double[i_size];
	this->i_size_solution = i_size;
	this->i_profit_of_best_solution = profit;
	for (int i = 0; i < i_size; i++)
	{
		this->pd_best_solution[i] = pd_solution[i];
	}
}

CRandomSearch::CRandomSearch(CMscnProblem * pd_c_mscn)
{
	this->pd_c_mscn = pd_c_mscn;
	this->pd_best_solution = NULL;
	this->i_size_solution = 0;
	this->i_profit_of_best_solution = 0;
}

CRandomSearch::~CRandomSearch()
{
	delete this->pd_c_mscn;
	if (this->pd_best_solution != NULL) delete this->pd_best_solution;
}

bool CRandomSearch::ifGetPdSolution()
{
	return *this->pd_c_mscn->pb_get_b_if_set_pd_problem();
}

void CRandomSearch::vGenerateRandomSolution(int i_count, int i_feed)
{
	CRandom* pr_pointer = new CRandom(i_feed);

	if (i_count > 0)
	{
		int profit = 0;
		int i_d_size = this->pd_c_mscn->iGetDSize();
		int i_f_size = this->pd_c_mscn->iGetFSize();
		int i_m_size = this->pd_c_mscn->iGetMSize();
		int i_s_size = this->pd_c_mscn->iGetSSize();
		int i_current_index = 0;
		while (i_current_index < i_count - 1)
		{
			double **xd_table = new double*[i_d_size];
			double **xf_table = new double*[i_f_size];
			double **xm_table = new double*[i_m_size];
			for (int i = 0; i < i_d_size; i++)
			{
				xd_table[i] = new double[i_f_size];
			}
			for (int i = 0; i < i_f_size; i++)
			{
				xf_table[i] = new double[i_m_size];
			}
			for (int i = 0; i < i_m_size; i++)
			{
				xm_table[i] = new double[i_s_size];
			}
			double d_min = D_MIN_XD;
			double d_max = D_MAX_XD;
			this->pd_c_mscn->generateForTwoDimentional(pr_pointer, xd_table, i_d_size, i_f_size, d_min, d_max);

			d_min = D_MIN_XF;
			d_max = D_MAX_XF;
			this->pd_c_mscn->generateForTwoDimentional(pr_pointer, xf_table, i_f_size, i_m_size, d_min, d_max);

			d_min = D_MIN_XM;
			d_max = D_MAX_XM;
			this->pd_c_mscn->generateForTwoDimentional(pr_pointer, xm_table, i_m_size, i_s_size, d_min, d_max);

			int i_correct_size_pd_solution = 4 + i_d_size * i_f_size + i_f_size * i_m_size + i_m_size * i_s_size;
			double *pd_solution = new double[i_correct_size_pd_solution];
			makePdSolution(pd_solution, xd_table, xf_table, xm_table, i_d_size, i_f_size, i_m_size, i_s_size);
			int *pi_number = new int();

		

			if (this->pd_c_mscn->bConstrainsSatisfied(pd_solution, i_correct_size_pd_solution, pi_number) && this->pd_c_mscn->bIfIntervalCorrect(pd_solution, i_correct_size_pd_solution))
			{
				profit =  this->pd_c_mscn->getDatasFromSolutionTables(xd_table, xf_table, xm_table);
				//cout << profit<<endl;
			}
			if (profit > this->i_profit_of_best_solution)
			{
				vCopyBestSolution(pd_solution, i_correct_size_pd_solution, profit);
			}
			delete pi_number;
			delete pd_solution;
			
			i_current_index++;
		}
		delete pr_pointer;
	}
	else 
	{
		cout << "i_count: " + i_count;
	}
	
}

void CRandomSearch::printBestSolutionWithProfit()
{
	if (this->pd_best_solution == NULL)
	{
		cout <<endl<< "bd_solution does not exist" << endl;
	}
	cout << "table of best solution";
	for (int i = 0; i < this->i_size_solution; i++)
	{
		cout << this->pd_best_solution[i] << endl;
	}
	cout << "profit :" << this->i_profit_of_best_solution;
}

void CRandomSearch::vPrintArray(double **pd_table, int i_line_size, int i_column_size)
{
	cout <<endl<<"printing array: "<< endl;
	for (int i = 0; i < i_line_size; i++)
	{
		for (int j = 0; j < i_column_size; j++)
		{
			cout << pd_table[i][j]<<endl;
		}
	}
}
