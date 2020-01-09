#include "CMscnProblem.h"

#include <string> 

int CMscnProblem::iGetSizeMustHave(int i_d_read_length, int i_f_read_length, int i_m_read_length, int i_s_read_length)
{
	int i_size_must_have = 0;
	i_size_must_have += 4;
	i_size_must_have += i_d_read_length * i_f_read_length;
	i_size_must_have += i_f_read_length * i_m_read_length;
	i_size_must_have += i_m_read_length * i_s_read_length;
	return i_size_must_have;
}

void CMscnProblem::generateForTwoDimentional(CRandom *cR, double** pd_table, int i_line_size, int i_column_size, double i_min, double i_max)
{
	 
	if (pd_table != NULL)
	{
		for (int i = 0; i < i_line_size; i++)
		{
			if (pd_table[i] == NULL)
			{
				pd_table[i] = new double[i_column_size];
			}
		}
	}
	else 
	{
		pd_table = new double*[i_line_size];
		for (int i = 0; i < i_column_size; i++)
		{
			pd_table[i] = new double[i_column_size];
		}
	}
	for (int i = 0; i < i_line_size; i++)
	{
		for (int j = 0; j < i_column_size; j++)
		{
			pd_table[i][j] = (*cR).iGetRandomDouble(i_min, i_max);
		}
	}
}

void CMscnProblem::generateForOneDimentional(CRandom * cR, double * pd_table, int i_size, double i_min, double i_max)
{
	if (pd_table == NULL)
	{
		pd_table = new double[i_size];
	}
	for (int i = 0; i < i_size; i++)
	{
		pd_table[i] = (*cR).iGetRandomDouble(i_min, i_max);
	}
	cout << endl << "w tablice" << endl;
	for (int i = 0; i < i_size; i++)
	{
		cout << pd_table[i] << endl;
	}
}

bool * CMscnProblem::pb_get_b_if_set_pd_problem()
{
	return this->b_if_set_pd_problem;
}

int CMscnProblem::iGetDSize()
{
	return this->i_d_size;
}

int CMscnProblem::iGetFSize()
{
	return this->i_f_size;
}

int CMscnProblem::iGetMSize()
{
	return this->i_m_size;
}

int CMscnProblem::iGetSSize()
{
	return this->i_s_size;
}

bool CMscnProblem::bIfIntervalCorrect(double * pd_solution, int i_size)
{

	if (*this->b_if_set_pd_problem)
	{
		double **xd_help = new double*[this->i_d_size];
		double **xf_help = new double*[this->i_f_size];
		double **xm_help = new double*[this->i_m_size];

		for (int i = 0; i < this->i_d_size; i++)
		{
			xd_help[i] = new double[this->i_f_size];
		}
		for (int i = 0; i < this->i_f_size; i++)
		{
			xf_help[i] = new double[this->i_m_size];
		}
		for (int i = 0; i < this->i_m_size; i++)
		{
			xm_help[i] = new double[this->i_s_size];
		}

		int i_current_index = 4;
		int i_line_index = 0;
		int i_column_index = 0;
		for (int i = i_current_index; i < i_current_index + this->i_d_size; i++)
		{
			if (i_column_index == this->i_f_size)
			{
				i_column_index = 0;
				i_line_index++;
			}
			xd_help[i_line_index][i_column_index] = pd_solution[i_current_index];
			i_column_index++;
		}

	    i_current_index += i_d_size;
		i_line_index = 0;
		i_column_index = 0;
		for (int i = i_current_index; i < i_current_index + this->i_f_size; i++)
		{
			if (i_column_index == this->i_m_size)
			{
				i_column_index = 0;
				i_line_index++;
			}
			xf_help[i_line_index][i_column_index] = pd_solution[i_current_index];
			i_column_index++;
		}

		i_current_index += i_f_size;
		i_line_index = 0;
		i_column_index = 0;
		for (int i = i_current_index; i < i_current_index + this->i_m_size; i++)
		{
			if (i_column_index == this->i_s_size)
			{
				i_column_index = 0;
				i_line_index++;
			}
			xm_help[i_line_index][i_column_index] = pd_solution[i_current_index];
			i_column_index++;
		}

		for (int i = 0; i < this->i_d_size; i++)
		{
			for (int j = 0; j < this->i_f_size; j++)
			{
				if (this->xd_min_max[i][j].first > xd_help[i][j] && this->xd_min_max[i][j].second < xd_help[i][j])
				{
					this->vDeleteTwoDementionalArray(xd_help, i_d_size);
					this->vDeleteTwoDementionalArray(xf_help, i_f_size);
					this->vDeleteTwoDementionalArray(xm_help, i_m_size);
					return false;
				}

			}
		}

		for (int i = 0; i < this->i_f_size; i++)
		{
			for (int j = 0; j < this->i_m_size; j++)
			{
				if (this->xf_min_max[i][j].first > xf_help[i][j] && this->xf_min_max[i][j].second < xf_help[i][j])
				{
					this->vDeleteTwoDementionalArray(xd_help, i_d_size);
					this->vDeleteTwoDementionalArray(xf_help, i_f_size);
					this->vDeleteTwoDementionalArray(xm_help, i_m_size);
					return false;
				}

			}
		}

		for (int i = 0; i < this->i_m_size; i++)
		{
			for (int j = 0; j < this->i_s_size; j++)
			{
				if (this->xm_min_max[i][j].first > xm_help[i][j] && this->xm_min_max[i][j].second < xm_help[i][j])
				{
					this->vDeleteTwoDementionalArray(xd_help, i_d_size);
					this->vDeleteTwoDementionalArray(xf_help, i_f_size);
					this->vDeleteTwoDementionalArray(xm_help, i_m_size);
					return false;
				}

			}
		}
		this->vDeleteTwoDementionalArray(xd_help, i_d_size);
		this->vDeleteTwoDementionalArray(xf_help, i_f_size);
		this->vDeleteTwoDementionalArray(xm_help, i_m_size);
		return true;
	}
	else 
	{
		return false;
	}
}

double CMscnProblem::getDatasFromSolutionTables(double ** xd_help, double ** xf_help, double ** xm_help)
{
	double d_finish_profit = 0;
	double d_k_t = 0;
	double d_k_u = 0;
	double d_p = 0;
	//sum cd xd
	for (int i = 0; i < this->i_d_size; i++)
	{
		for (int j = 0; j < this->i_f_size; j++)
		{
			d_k_t += this->cd_table[i][j] * xd_help[i][j];
		}
	}

	//sum cf xf
	for (int i = 0; i < this->i_f_size; i++)
	{
		for (int j = 0; j < this->i_m_size; j++)
		{
			d_k_t += this->cf_table[i][j] * xf_help[i][j];
		}
	}

	//sum cm cm

	for (int i = 0; i < this->i_m_size; i++)
	{
		for (int j = 0; j < this->i_s_size; j++)
		{
			d_k_t += this->cm_table[i][j] * xm_help[i][j];
		}
	}

	//d_k_u

	for (int i = 0; i < this->i_d_size; i++)
	{
		double d_sum_xd_f = 0;
		double d_pseudo_b_helper = 0;
		for (int j = 0; j < this->i_f_size; j++)
		{
			d_sum_xd_f += xd_help[i][j];
		}
		if (d_sum_xd_f > 0) d_pseudo_b_helper = 1;
		d_k_u += d_pseudo_b_helper * this->ud_table[i];
	}

	for (int i = 0; i < this->i_f_size; i++)
	{
		double d_sum_xf_m = 0;
		double d_pseudo_b_helper = 0;
		for (int j = 0; j < this->i_m_size; j++)
		{
			d_sum_xf_m += xf_help[i][j];
		}
		if (d_sum_xf_m > 0) d_pseudo_b_helper = 1;
		d_k_u += d_pseudo_b_helper * this->uf_table[i];
	}

	for (int i = 0; i < this->i_m_size; i++)
	{
		double d_sum_xm_s = 0;
		double d_pseudo_b_helper = 0;
		for (int j = 0; j < this->i_s_size; j++)
		{
			d_sum_xm_s += xm_help[i][j];
		}
		if (d_sum_xm_s > 0) d_pseudo_b_helper = 1;
		d_k_u += d_pseudo_b_helper * this->um_table[i];
	}
	//d_p
	for (int i = 0; i < this->i_m_size; i++)
	{
		for (int j = 0; j < this->i_s_size; j++)
		{
			d_p += this->p_table[j] * xm_help[i][j];
		}
	}
	d_finish_profit = d_p - d_k_t - d_k_u;
	return d_finish_profit;
}

CMscnProblem::CMscnProblem()
{
	this->b_if_good_init = new bool;
	this->b_if_set_pd_problem = new bool;
	this->b_if_good_pd_solution = new bool;
	this->b_if_was_set_value = new bool;
	this->b_if_set_pd_solution = new bool;
	this->b_if_set_sizes = new bool;
	*(this->b_if_set_sizes) = false;
	*(this->b_if_set_pd_solution) = false;
	*(this->b_if_good_init) = true;
	*(this->b_if_good_pd_solution) = true;
	*(this->b_if_was_set_value) = false;
	*(this->b_if_set_pd_problem) = false;
	this->i_d_size = 0;
	this->i_f_size = 0;
	this->i_m_size = 0;
	this->i_s_size = 0;
}


CMscnProblem::~CMscnProblem()
{
	//delete one-dimentional double arrays
	this->vDeleteOneDimensionalArray(this->sd_table);
	this->vDeleteOneDimensionalArray(this->sf_table);
	this->vDeleteOneDimensionalArray(this->sm_table);
	this->vDeleteOneDimensionalArray(this->ss_table);
	//delete two-dimensional double arrays
	this->vDeleteTwoDementionalArray(this->cd_table, this->i_d_size);
	this->vDeleteTwoDementionalArray(this->cf_table, this->i_f_size);
	this->vDeleteTwoDementionalArray(this->cm_table,this->i_m_size);
	//delete bool pointers.
	delete this->b_if_was_set_value;
	delete this->b_if_good_init;
	delete this->b_if_good_pd_solution;
	delete this->b_if_set_pd_problem;
	delete this->b_if_set_pd_solution;
	delete this->b_if_set_sizes;
	//delete another parametrs
	this->vDeleteOneDimensionalArray(this->ud_table);
	this->vDeleteOneDimensionalArray(this->uf_table);
	this->vDeleteOneDimensionalArray(this->um_table);
	this->vDeleteOneDimensionalArray(this->p_table);

	this->vDeleteTwoDementionalArray(this->xd_table, this->i_d_size);
	this->vDeleteTwoDementionalArray(this->xf_table, this->i_f_size);
	this->vDeleteTwoDementionalArray(this->xm_table, this->i_m_size);

	this->vDeleteTwoDementionalArray(this->xd_min_max, this->i_d_size);
	this->vDeleteTwoDementionalArray(this->xf_min_max, this->i_f_size);
	this->vDeleteTwoDementionalArray(this->xm_min_max, this->i_m_size);
}

void CMscnProblem::vDeleteOneDimensionalArray(double* pd_table)
{
	if (pd_table != NULL) delete pd_table;
}

void CMscnProblem::vDeleteTwoDementionalArray(double** pd_table, int i_size)
{
	if (pd_table != NULL)
	{
		for (int i = 0; i < i_size; i++)
		{
			//array of references has NULLs instead references
			if (pd_table[i] != NULL) delete pd_table[i];
		}
		delete pd_table;
	}
}

void CMscnProblem::vDeleteTwoDementionalArray(std::pair<double, double>** pp_pointer, int i_size)
{
	if (pp_pointer != NULL)
	{
		for (int i = 0; i < i_size; i++)
		{
			if (pp_pointer[i] != NULL) delete pp_pointer[i];
		}
		delete pp_pointer;
	}
}

void CMscnProblem::vPrintBoolPointer(bool * pb_pointer)
{
	if (pb_pointer != NULL)
	{
		cout << *pb_pointer << endl;
	}
	else 
	{
		cout << "mistake initial bool pointer";
	}
}

void CMscnProblem::vPrintOneDemensionalArray(double * pd_table, int i_size)
{
	if (pd_table != NULL)
	{

		for (int i = 0; i < i_size; i++)
		{
			cout << pd_table[i] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "mistaken init (double *) pd_table ";
	}
}

void CMscnProblem::vPrintTwoDementionalArray(double ** pd_table, int i_line_size, int i_column_size)
{
	if (pd_table == NULL)
	{
		cout << "bad init (double **)pd_table"<<endl;
	}
	else 
	{
		bool if_good_init = true;
		for (int i = 0; i < i_line_size; i++)
		{
			if (pd_table[i] == NULL)
			{
				if_good_init = false;
			}
		}
		if (!if_good_init)
		{
			cout << "bad init (double **)pd_table";
		}
		else 
		{
			for (int i = 0; i < i_line_size; i++)
			{
				for (int j = 0; j < i_column_size; j++)
				{
					cout << pd_table[i][j] << " ";
				}
				cout << endl;
			}
		}
	}
}

void CMscnProblem::vPrintTwoDementionalArray(std::pair<double, double>** pp_pointer, int i_line_size, int i_column_size)
{
	if (pp_pointer == NULL)
	{
		cout << "bad init (std::pair<double, double>**)pd_table";
	}
	else
	{
		bool if_good_init = true;
		for (int i = 0; i < i_line_size; i++)
		{
			if (pp_pointer[i] == NULL)
			{
				if_good_init = false;
			}
		}
		if (!if_good_init)
		{
			cout << "bad init (std::pair<double, double>**)pd_table";
		}
		else
		{
			for (int i = 0; i < i_line_size; i++)
			{
				for (int j = 0; j < i_column_size; j++)
				{
					cout << pp_pointer[i][j].first << " " << pp_pointer[i][j].second << "     ";
				}
				cout << endl;
			}
		}
	}
}



bool CMscnProblem::bGetIfGoodInit()
{
	return *(this->b_if_good_init);
}



bool CMscnProblem::bGetIfGoodPdSolution()
{
	return *(this->b_if_good_pd_solution);
}

void CMscnProblem::vSetSizes(int i_d_length, int i_f_length, int i_m_length, int i_s_length)
{
	if (i_d_length <= 0 || i_f_length <= 0 || i_m_length <= 0 || i_s_length <= 0)
	{
		*(this->b_if_good_init) = false;
	}
	else
	{
		if (this->b_if_was_set_value)
		{
			//delete one-dimentional double arrays
			this->vDeleteOneDimensionalArray(this->sd_table);
			this->vDeleteOneDimensionalArray(this->sf_table);
			this->vDeleteOneDimensionalArray(this->sm_table);
			this->vDeleteOneDimensionalArray(this->ss_table);
			//add new lines 
			this->vDeleteOneDimensionalArray(this->ud_table);
			this->vDeleteOneDimensionalArray(this->uf_table);
			this->vDeleteOneDimensionalArray(this->um_table);
			//delete two-dimensional double arrays
			this->vDeleteTwoDementionalArray(this->cd_table, this->i_d_size);
			this->vDeleteTwoDementionalArray(this->cf_table, this->i_f_size);
			this->vDeleteTwoDementionalArray(this->cm_table, this->i_m_size);
			//add new lines 

			//delete bool pointers
			delete this->b_if_was_set_value;
			delete this->b_if_good_init;
			delete this->b_if_good_pd_solution;
			//init bool pointers
			this->b_if_was_set_value = new bool;
			this->b_if_good_init = new bool;
			this->b_if_good_pd_solution = new bool;
		
		}
	

		//new part
		*(this->b_if_was_set_value) = true;
		*(this->b_if_good_init) = true;
		*(this->b_if_good_pd_solution) = true;
		
		this->cd_table = new double*[i_d_length];
		this->cf_table = new double*[i_f_length];
		this->cm_table = new double*[i_m_length];
		for (int i = 0; i < i_d_length; i++)
		{
			this->cd_table[i] = new double[i_f_length];
		}
		for (int i = 0; i < i_f_length; i++)
		{
			this->cf_table[i] = new double[i_m_length];
		}
		for (int i = 0; i < i_m_length; i++)
		{
			this->cm_table[i] = new double[i_s_length];
		}
		this->sd_table = new double[i_d_length];
		this->sf_table = new double[i_f_length];
		this->sm_table = new double[i_m_length];
		this->ss_table = new double[i_s_length];
		this->i_d_size = i_d_length;
		this->i_f_size = i_f_length;
		this->i_m_size = i_m_length;
		this->i_s_size = i_s_length;
		*(this->b_if_was_set_value) = true;
		*this->b_if_set_sizes = true;

		//add new lines
		this->ud_table = new double[i_d_length];
		this->uf_table = new double[i_f_length];
		this->um_table = new double[i_m_length];
	}
}

bool CMscnProblem::bsetValueCD(double d_value, int i_x_index, int i_y_index)
{
	if (!*(this->b_if_good_init) || i_x_index < 0 || i_x_index >= this->i_d_size || i_y_index < 0 || i_y_index >= this->i_f_size)
	{
		return false;
	} 
	else
	{
		this->cd_table[i_x_index][i_y_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueCF(double d_value, int i_x_index, int i_y_index)
{
	if (!*(this->b_if_good_init) || i_x_index < 0 || i_x_index >= this->i_f_size || i_y_index < 0 || i_y_index >= this->i_m_size)
	{
		return false;
	}
	else
	{
		this->cf_table[i_x_index][i_y_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueCM(double d_value, int i_x_index, int i_y_index)
{
	if (!*(this->b_if_good_init) || i_x_index < 0 || i_x_index >= this->i_m_size || i_y_index < 0 || i_y_index >= this->i_s_size)
	{
		return false;
	}
	else
	{
		this->cm_table[i_x_index][i_y_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueSD(double d_value, int i_index)
{
	if (!*(this->b_if_good_init) || i_index < 0 || i_index >= this->i_d_size)
	{
		return false;
	}
	else 
	{
		this->sd_table[i_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueSF(double d_value, int i_index)
{
	if (!*(this->b_if_good_init) || i_index < 0 || i_index >= this->i_f_size)
	{
		return false;
	}
	else
	{
		this->sf_table[i_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueSM(double d_value, int i_index)
{
	if (!*(this->b_if_good_init) || i_index < 0 || i_index >= this->i_f_size)
	{
		return false;
	}
	else
	{
		this->sf_table[i_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bsetValueSS(double d_value, int i_index)
{
	if (!*(this->b_if_good_init) || i_index < 0 || i_index >= this->i_s_size)
	{
		return false;
	}
	else
	{
		this->ss_table[i_index] = d_value;
		return true;
	}
}

bool CMscnProblem::bGetDatasFromProblem(double * pd_problem, int i_size)
{
	if (pd_problem == NULL || i_size <= 0) return false;
	for (int i = 0; i < i_size; i++)
	{
		double num_help = pd_problem[i];
		if (pd_problem[i] == NULL) return false;
	}
	for (int i = 0; i < i_size; i++)
	{
		if (pd_problem[i] <= 0) return false;
	}
	int i_current_index_pd_problem = 0;
	//add sizes
	this->i_d_size = pd_problem[i_current_index_pd_problem++];
	this->i_f_size = pd_problem[i_current_index_pd_problem++];
	this->i_m_size = pd_problem[i_current_index_pd_problem++];
	this->i_s_size = pd_problem[i_current_index_pd_problem++];

	this->vSetSizes(this->i_d_size, this->i_f_size, this->i_m_size, this->i_s_size);
	//add s
	int i_current_table_index_help = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_d_size; i++, i_current_table_index_help++)
	{
		this->sd_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_d_size;
	i_current_table_index_help = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_f_size; i++, i_current_table_index_help++)
	{
		this->sf_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_f_size;
	i_current_table_index_help = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_m_size; i++, i_current_table_index_help++)
	{
		this->sm_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_m_size;
	i_current_table_index_help = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_s_size; i++, i_current_table_index_help++)
	{
		this->ss_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_s_size;
	i_current_table_index_help = 0;

	int i_line_index = 0;
	int i_column_index = 0;

	
	//odzyt cd cf cm
	int i_tab_length = this->i_d_size * this->i_f_size;
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++)
	{
		if (i_column_index == this->i_f_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->cd_table[i_line_index][i_column_index] = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;

	i_line_index = 0;
	i_column_index = 0;
	i_tab_length = this->i_f_size * this->i_m_size;
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++)
	{
		if (i_column_index == this->i_m_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->cf_table[i_line_index][i_column_index] = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;

	i_line_index = 0;
	i_column_index = 0;
	i_tab_length = this->i_m_size * this->i_s_size;
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++)
	{
		if (i_column_index == this->i_s_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->cm_table[i_line_index][i_column_index] = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;

	//wczyt ud wartosi
	i_current_table_index_help = 0;
	this->ud_table = new double[this->i_d_size];
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_d_size; i++, i_current_table_index_help++)
	{
		this->ud_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_d_size;
	//wczyt uf wartosi
	i_current_table_index_help = 0;
	this->uf_table = new double[this->i_f_size];
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_f_size; i++, i_current_table_index_help++)
	{
		this->uf_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_f_size;
	//wczyt um wartosci
	i_current_table_index_help = 0;
	this->um_table = new double[this->i_m_size];
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_m_size; i++, i_current_table_index_help++)
	{
		this->um_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_m_size;
	//wczyt p wartosci
	i_current_table_index_help = 0;
	this->p_table = new double[this->i_s_size];
	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + this->i_s_size; i++, i_current_table_index_help++)
	{
		this->p_table[i_current_table_index_help] = pd_problem[i];
	}
	i_current_index_pd_problem += this->i_s_size;
	//wczyt xdminmax
	//init 
	this->xd_min_max = new std::pair<double, double>*[this->i_d_size];
	for (int i = 0; i < this->i_d_size; i++)
	{
		this->xd_min_max[i] = new std::pair<double, double>[this->i_f_size];
	}

	i_tab_length = this->i_d_size * this->i_f_size * 2;
	i_line_index = 0;
	i_column_index = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++, i_column_index++)
	{
		if (i_column_index == this->i_f_size)
		{
			i_line_index++;
			i_column_index = 0;
		}
		this->xd_min_max[i_line_index][i_column_index].first = pd_problem[i++];
		this->xd_min_max[i_line_index][i_column_index].second = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;

	//wczyt xfminmax
	this->xf_min_max = new std::pair<double, double>*[this->i_f_size];
	for (int i = 0; i < this->i_f_size; i++)
	{
		this->xf_min_max[i] = new std::pair<double, double>[this->i_m_size];
	}

	i_tab_length = this->i_f_size * this->i_m_size * 2;
	i_line_index = 0;
	i_column_index = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++, i_column_index++)
	{
		if (i_column_index == this->i_m_size)
		{
			i_line_index++;
			i_column_index = 0;
		}
		this->xf_min_max[i_line_index][i_column_index].first = pd_problem[i++];
		this->xf_min_max[i_line_index][i_column_index].second = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;

	//wczyt xmminmax

	this->xm_min_max = new std::pair<double, double>*[this->i_m_size];
	for (int i = 0; i < this->i_m_size; i++)
	{
		this->xm_min_max[i] = new std::pair<double, double>[this->i_s_size];
	}

	i_tab_length = this->i_m_size * this->i_s_size * 2;
	i_line_index = 0;
	i_column_index = 0;

	for (int i = i_current_index_pd_problem; i < i_current_index_pd_problem + i_tab_length; i++, i_column_index++)
	{
		if (i_column_index == this->i_s_size)
		{
			i_line_index++;
			i_column_index = 0;
		}
		this->xm_min_max[i_line_index][i_column_index].first = pd_problem[i++];
		this->xm_min_max[i_line_index][i_column_index].second = pd_problem[i];
	}
	i_current_index_pd_problem += i_tab_length;
	*this->b_if_set_pd_problem = true;
	return true;
}

bool CMscnProblem::bGetDatasFromSolution(double * pd_solution, int i_size)
{
	//x can be 0
	if (i_size <= 0 || pd_solution == NULL || !(*this->b_if_set_pd_problem)) return false;
	for (int i = 0; i < i_size; i++)
	{
		if (pd_solution[i] == NULL) return false;
	}
	for (int i = 0; i < i_size; i++)
	{
		if (pd_solution[i] < 0) return false;
	}
	int i_current_index_pd_solution = 0;
	if (this->i_d_size != pd_solution[i_current_index_pd_solution++]) return false;
	if (this->i_f_size != pd_solution[i_current_index_pd_solution++]) return false;
	if (this->i_m_size != pd_solution[i_current_index_pd_solution++]) return false;
	if (this->i_s_size != pd_solution[i_current_index_pd_solution++]) return false;
	//xd two-dementional

	//init
	this->xd_table = new double*[this->i_d_size];
	for (int i = 0; i < this->i_d_size; i++)
	{
		this->xd_table[i] = new double[this->i_f_size];
	}

	int i_tab_length_help = this->i_d_size * this->i_f_size;
	int i_line_index = 0;
	int i_column_index = 0;
	for (int i = i_current_index_pd_solution; i < i_tab_length_help + i_current_index_pd_solution; i++)
	{
		if (i_column_index == this->i_f_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->xd_table[i_line_index][i_column_index] = pd_solution[i];
	}
	i_current_index_pd_solution += i_tab_length_help;
	//xf

	//init
	this->xf_table = new double*[this->i_f_size];
	for (int i = 0; i < this->i_f_size; i++)
	{
		this->xf_table[i] = new double[this->i_m_size];
	}

	i_tab_length_help = this->i_f_size * this->i_m_size;
	i_line_index = 0;
	i_column_index = 0;
	for (int i = i_current_index_pd_solution; i < i_tab_length_help + i_current_index_pd_solution; i++)
	{
		if (i_column_index == this->i_m_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->xf_table[i_line_index][i_column_index] = pd_solution[i];
	}
	i_current_index_pd_solution += i_tab_length_help;

	//xm

	//init
	this->xm_table = new double*[this->i_m_size];
	for (int i = 0; i < this->i_m_size; i++)
	{
		this->xm_table[i] = new double[this->i_s_size];
	}

	i_tab_length_help = this->i_m_size * this->i_s_size;
    i_line_index = 0;
	i_column_index = 0;
	for (int i = i_current_index_pd_solution; i < i_tab_length_help + i_current_index_pd_solution; i++)
	{
		if (i_column_index == this->i_s_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		this->xm_table[i_line_index][i_column_index] = pd_solution[i];
	}
	i_current_index_pd_solution += i_tab_length_help;
	*this->b_if_set_pd_solution = true;
	return true;
}

void CMscnProblem::vPrintAllDatas()
{
	cout << "b_if_good_init" << endl;
	this->vPrintBoolPointer(this->b_if_good_init);

	cout << "b_if_good_pd_solution" << endl;
	this->vPrintBoolPointer(this->b_if_good_pd_solution);

	cout << "b_if_was_set_value" << endl;
	this->vPrintBoolPointer(this->b_if_was_set_value);

	cout << "b_if_set_pd_problem" << endl;
	this->vPrintBoolPointer(this->b_if_set_pd_problem);

	cout << "cd_table" << endl;
	this->vPrintTwoDementionalArray(this->cd_table, this->i_d_size, this->i_f_size);

	cout << "cf_table" << endl;
	this->vPrintTwoDementionalArray(this->cf_table, this->i_f_size, this->i_m_size);
	
	cout << "cm_table" << endl;
	this->vPrintTwoDementionalArray(this->cm_table, this->i_m_size, this->i_s_size);

	cout << "sd_table" <<endl;
	this->vPrintOneDemensionalArray(this->sd_table, this->i_d_size);

    cout << "sf_table" << endl;
	this->vPrintOneDemensionalArray(this->sf_table, this->i_f_size);

	cout << "sm_table" << endl;
	this->vPrintOneDemensionalArray(this->sm_table, this->i_m_size);

	cout << "ss_table" << endl;
	this->vPrintOneDemensionalArray(this->ss_table, this->i_s_size);

	cout << "ud_table" << endl;
	this->vPrintOneDemensionalArray(this->ud_table, this->i_d_size);

	cout << "uf_table" << endl;
	this->vPrintOneDemensionalArray(this->uf_table, this->i_f_size);

	cout << "um_table" << endl;
	this->vPrintOneDemensionalArray(this->um_table, this->i_m_size);

	cout << "p_table" << endl;
	this->vPrintOneDemensionalArray(this->p_table, this->i_s_size);

	cout << "xd_min_max" << endl;
	this->vPrintTwoDementionalArray(this->xd_min_max, this->i_d_size, this->i_f_size);

	cout << "xf_min_max" << endl;
	this->vPrintTwoDementionalArray(this->xf_min_max, this->i_f_size, this->i_m_size);

	cout << "xm_min_max" << endl;
	this->vPrintTwoDementionalArray(this->xm_min_max, this->i_m_size, this->i_s_size);

	cout << "xd_table" << endl;
	this->vPrintTwoDementionalArray(this->xd_table, this->i_d_size, this->i_f_size);

	cout << "xf_table" << endl;
	this->vPrintTwoDementionalArray(this->xf_table, this->i_f_size, this->i_m_size);

	cout << "xm_table" << endl;
	this->vPrintTwoDementionalArray(this->xm_table, this->i_m_size, this->i_s_size);

	cout << "i_d_size" << endl;
	cout << this->i_d_size << endl;

	cout << "i_f_size" << endl;
	cout << this->i_f_size << endl;

	cout << "i_m_size" << endl;
	cout << this->i_m_size << endl;

	cout << "i_s_size" << endl;
	cout << this->i_s_size << endl;
}

double CMscnProblem::dGetQuality(double * pd_solution, int i_size, double * pd_mistake)
{
	if (pd_solution == NULL)
	{
		*pd_mistake = D_MISTAKE_TABLE_PD_SOLUTION_NOT_EXIST;
		return NULL;
	}
	for (int i = 0; i < i_size; i++)
	{
		if (pd_solution[i] == NULL)
		{
			*pd_mistake = D_MISTAKE_TABLE_PD_SOLUTION_NOT_EXIST;
			return NULL;
		}
	}
	if (!(*this->b_if_set_pd_problem)) 
	{
		*pd_mistake = D_MISTAKE_ALREADY_EXIST_PD_PROBLEM;
		return NULL;
	}
	else 
	{
		if (!this->bGetDatasFromSolution(pd_solution, i_size))
		{
			*pd_mistake = D_ANOTHER_PROBLEM;
			return NULL;
		}
		else 
		{
			double d_finish_profit = 0;
			double d_k_t = 0;
			double d_k_u = 0;
			double d_p = 0;
			//sum cd xd
			for (int i = 0; i < this->i_d_size; i++)
			{
				for (int j = 0; j < this->i_f_size; j++)
				{
					d_k_t += this->cd_table[i][j] * this->xd_table[i][j];
				}
			}

			//sum cf xf
			for (int i = 0; i < this->i_f_size; i++)
			{
				for (int j = 0; j < this->i_m_size; j++)
				{
					d_k_t += this->cf_table[i][j] * this->xf_table[i][j];
				}
			}

			//sum cm cm

			for (int i = 0; i < this->i_m_size; i++)
			{
				for (int j = 0; j < this->i_s_size; j++)
				{
					d_k_t += this->cm_table[i][j] * this->xm_table[i][j];
				}
			}

			//d_k_u

			for (int i = 0; i < this->i_d_size; i++)
			{
				double d_sum_xd_f = 0;
				double d_pseudo_b_helper = 0;
				for (int j = 0; j < this->i_f_size; j++)
				{
					d_sum_xd_f += this->xd_table[i][j];
				}
				if (d_sum_xd_f > 0) d_pseudo_b_helper = 1;
				d_k_u += d_pseudo_b_helper * this->ud_table[i];
			}

			for (int i = 0; i < this->i_f_size; i++)
			{
				double d_sum_xf_m = 0;
				double d_pseudo_b_helper = 0;
				for (int j = 0; j < this->i_m_size; j++)
				{
					d_sum_xf_m += this->xf_table[i][j];
				}
				if (d_sum_xf_m > 0) d_pseudo_b_helper = 1;
				d_k_u += d_pseudo_b_helper * this->uf_table[i];
			}

			for (int i = 0; i < this->i_m_size; i++)
			{
				double d_sum_xm_s = 0;
				double d_pseudo_b_helper = 0;
				for (int j = 0; j < this->i_s_size; j++)
				{
					d_sum_xm_s += this->xm_table[i][j];
				}
				if (d_sum_xm_s > 0) d_pseudo_b_helper = 1;
				d_k_u += d_pseudo_b_helper * this->um_table[i];
			}
			//d_p
			for (int i = 0; i < this->i_m_size; i++)
			{
				for (int j = 0; j < this->i_s_size; j++)
				{
					d_p += this->p_table[j] * this->xm_table[i][j];
				}
			}
			d_finish_profit = d_p - d_k_t - d_k_u;
			*pd_mistake = D_NO_NISTAKE;
			return d_finish_profit;
		}
	}
}

bool CMscnProblem::writeProblem(string s_file_name)
{
	string s_to_write = "";
	s_to_write += "D "+to_string(this->i_d_size);
	s_to_write += "\n";

	s_to_write += "F "; s_to_write += to_string(this->i_f_size);
	s_to_write += "\n";
	
	s_to_write += "M " + to_string(this->i_m_size);
	s_to_write += "\n";

	s_to_write += "S " + to_string(this->i_s_size);
	s_to_write += "\n";

	s_to_write += "sd";
	s_to_write += "\n";
	for (int i = 0; i < this->i_d_size; i++)
	{
		s_to_write += to_string(this->sd_table[i]);
		if (i != this->i_d_size) s_to_write += " ";
	}

	s_to_write += "\n";
	s_to_write += "sf";
	s_to_write += "\n";
	cout << endl << "-------------------------------" << endl;
	cout << s_to_write.c_str() << endl;
	for (int i = 0; i < this->i_f_size; i++)
	{
		double d_num = sf_table[i];
		

		auto str = std::to_string(d_num);
		s_to_write += str;

		if (i != this->i_f_size) s_to_write += " ";
	}

	cout << endl << "-------------------------------" << endl;
	cout << s_to_write.c_str() << endl;

	s_to_write += "\n";
	s_to_write += "sm";
	s_to_write += "\n";

	for (int i = 0; i < this->i_m_size; i++)
	{
		s_to_write += to_string(this->sm_table[i]);
		if (i != this->i_m_size) s_to_write += " ";
	}

	s_to_write += "\n";
	s_to_write += "ss";
	s_to_write += "\n";

	for (int i = 0; i < this->i_s_size; i++)
	{
		s_to_write += to_string(this->ss_table[i]);
		if (i != this->i_s_size) s_to_write += " ";
	}

	s_to_write += "\n";
	s_to_write += "cd";
	s_to_write += "\n";
	

	for (int i = 0; i < this->i_d_size; i++)
	{
		for (int j = 0; j < this->i_f_size; j++)
		{
			s_to_write += to_string(this->cd_table[i][j]);
			if (j != this->i_f_size - 1)
			{
				s_to_write += " ";
			}
		}
		if (i != i_d_size - 1) s_to_write += "\n";
	}



	s_to_write += "\n";
	s_to_write += "cf";
	s_to_write += "\n";


	for (int i = 0; i < this->i_f_size; i++)
	{
		for (int j = 0; j < this->i_m_size; j++)
		{
			s_to_write += to_string(this->cf_table[i][j]);
			if (j != this->i_m_size - 1)
			{
				s_to_write += " ";
			}
		}
		if (i != i_f_size - 1) s_to_write += "\n";
	}



	s_to_write += "\n";
	s_to_write += "cm";
	s_to_write += "\n";


	for (int i = 0; i < this->i_m_size; i++)
	{
		for (int j = 0; j < this->i_s_size; j++)
		{
			s_to_write += to_string(this->cm_table[i][j]);
			if (j != this->i_s_size - 1)
			{
				s_to_write += " ";
			}
		}
		if (i != i_m_size - 1) s_to_write += "\n";
	}




	s_to_write += "\n";
	s_to_write += "ud";
	s_to_write += "\n";

	for (int i = 0; i < this->i_d_size; i++)
	{
		s_to_write += to_string(this->ud_table[i]);
		if (i != i_d_size - 1) s_to_write += " ";
	}



	s_to_write += "\n";
	s_to_write += "uf";
	s_to_write += "\n";

	for (int i = 0; i < this->i_f_size; i++)
	{
		s_to_write += to_string(this->uf_table[i]);
		if (i != i_f_size - 1) s_to_write += " ";
	}





	s_to_write += "\n";
	s_to_write += "um";
	s_to_write += "\n";

	for (int i = 0; i < this->i_m_size; i++)
	{
		s_to_write += to_string(this->um_table[i]);
		if (i != i_m_size - 1) s_to_write += " ";
	}



	s_to_write += "\n";
	s_to_write += "p";
	s_to_write += "\n";

	for (int i = 0; i < this->i_s_size; i++)
	{
		s_to_write += to_string(this->p_table[i]);
		if (i != i_s_size - 1) s_to_write += " ";
	}

	s_to_write += "\n";
	s_to_write += "xdminmax";
	s_to_write += "\n";


	for (int i = 0; i < this->i_d_size; i++)
	{
		for (int j = 0; j < this->i_f_size; j++)
		{
			s_to_write += to_string(this->xd_min_max[i][j].first) + " " + to_string(this->xd_min_max[i][j].second);
			if (j != this->i_f_size - 1) s_to_write += " ";
		}
		if (i != this->i_d_size - 1) s_to_write += "\n";
	}



	s_to_write += "\n";
	s_to_write += "xfminmax";
	s_to_write += "\n";


	for (int i = 0; i < this->i_f_size; i++)
	{
		for (int j = 0; j < this->i_m_size; j++)
		{
			s_to_write += to_string(this->xf_min_max[i][j].first) + " " + to_string(this->xf_min_max[i][j].second);
			if (j != this->i_m_size - 1) s_to_write += " ";
		}
		if (i != this->i_f_size - 1) s_to_write += "\n";
	}

	s_to_write += "\n";
	s_to_write += "xmminmax";
	s_to_write += "\n";


	for (int i = 0; i < this->i_m_size; i++)
	{
		for (int j = 0; j < this->i_s_size; j++)
		{
			s_to_write += to_string(this->xm_min_max[i][j].first) + " " + to_string(this->xm_min_max[i][j].second);
			if (j != this->i_s_size - 1) s_to_write += " ";
		}
		if (i != this->i_m_size - 1) s_to_write += "\n";
	}

	cout << endl << "-------------------------------" << endl;
	cout << s_to_write.c_str() <<endl;
	FILE *file = fopen(s_file_name.c_str(), "w");

	bool b_to_return = false;
	if (file != NULL) // если есть доступ к файлу,
	{
		// инициализируем строку
		bool result = fputs(s_to_write.c_str(), file); // и записываем ее в файл
		if (!result) // если запись произошла успешно
		{
			cout << "no mistakes in open file and put in " << endl; // выводим сообщение
			b_to_return = !result;
		}
	}
	else
		cout << "mistakes in open file";
	fclose(file);
	
	return b_to_return;
}

bool CMscnProblem::writeSolution(string s_file_name)
{
	string s_to_write = "";
	s_to_write += "D " + to_string(this->i_d_size);
	s_to_write += "\n";
	s_to_write += "F " + to_string(this->i_d_size);
	s_to_write += "\n";
	s_to_write += "M " + to_string(this->i_d_size);
	s_to_write += "\n";
	s_to_write += "S " + to_string(this->i_s_size);
	s_to_write += "\n";

	//xd

	s_to_write += "xd";
	s_to_write += "\n";
	for (int i = 0; i < this->i_d_size; i++)
	{
		for (int j = 0; j < this->i_f_size; j++)
		{
			s_to_write += to_string(this->xd_table[i][j]);
			if (j != this->i_f_size - 1) s_to_write += " ";
		}
		if (this->i_d_size - 1 != i) s_to_write += "\n";
	}

	s_to_write += "\n";
	s_to_write += "xf";
	s_to_write += "\n";
	for (int i = 0; i < this->i_f_size; i++)
	{
		for (int j = 0; j < this->i_m_size; j++)
		{
			s_to_write += to_string(this->xf_table[i][j]);
			if (j != this->i_m_size - 1) s_to_write += " ";
		}
		if (this->i_f_size - 1 != i) s_to_write += "\n";
	}


	s_to_write += "\n";
	s_to_write += "xm";
	s_to_write += "\n";
	for (int i = 0; i < this->i_m_size; i++)
	{
		for (int j = 0; j < this->i_s_size; j++)
		{
			s_to_write += to_string(this->xm_table[i][j]);
			if (j != this->i_s_size - 1) s_to_write += " ";
		}
		if (this->i_m_size - 1 != i) s_to_write += "\n";
	}


	FILE *file = fopen(s_file_name.c_str(), "w");

	bool b_to_return = false;
	if (file != NULL) // если есть доступ к файлу,
	{
		// инициализируем строку
		bool result = fputs(s_to_write.c_str(), file); // и записываем ее в файл
		if (!result) // если запись произошла успешно
		{
			cout << "no mistakes in open file and put in " << endl; // выводим сообщение
			b_to_return = !result;
		}

	}
	else
		cout << "nistakes in open file";
	fclose(file);

	return b_to_return;
}

bool CMscnProblem::bConstrainsSatisfied(double *pd_solution, int i_size, int *pi_error_num)
{
	if (i_size < 4)
	{
		*pi_error_num = I_ERROR_SIZE;
		return false;
	}
	if (pd_solution == NULL)
	{
		*pi_error_num = I_ERROR_NULL_POINTER;
		return false;
	}
	int i_d_read_length = pd_solution[0];
	int i_f_read_length = pd_solution[1];
	int i_m_read_length = pd_solution[2];
	int i_s_read_length = pd_solution[3];
	int i_size_must_have = iGetSizeMustHave(i_d_read_length, i_f_read_length, i_m_read_length, i_s_read_length);
	if (i_size != i_size_must_have)
	{
		*pi_error_num = I_ERROR_SIZE;
		return false;
	}
	for (int i = 0; i < i_size_must_have; i++)
	{
		if (pd_solution[i] <= 0)
		{
			*pi_error_num = I_ERROR_VALUE_INTERVAL;
			return false;
		}
	}

	if (!*this->b_if_set_pd_problem)
	{
		*pi_error_num = I_NOT_SET_PD_PROBLEM;
		return false;
	}
	//create help fake solution

	double **xd_help = new double* [pd_solution[0]];
	double **xf_help = new double* [pd_solution[1]];
	double **xm_help = new double* [pd_solution[2]];

	for (int i = 0; i < this->i_d_size; i++)
	{
	     xd_help[i] = new double[this->i_f_size];
	}

	for (int i = 0; i < this->i_f_size; i++)
	{
		xf_help[i] = new double[this->i_m_size];
	}

	for (int i = 0; i < this->i_m_size; i++)
	{
		xm_help[i] = new double[this->i_s_size];
	}

	int i_current_index = 4;
	int i_line_index = 0;
	int i_column_index = 0;
	int i_indexes_to_go = this->i_d_size * this->i_f_size;
	for (int i = i_current_index; i < i_current_index + i_indexes_to_go; i++)
	{
		if (i_column_index == this->i_f_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		xd_help[i_line_index][i_column_index] = pd_solution[i];
		i_column_index++;
	}
	i_current_index += i_indexes_to_go;

	i_line_index = 0;
	i_column_index = 0;
	i_indexes_to_go = this->i_f_size * this->i_m_size;
	for (int i = i_current_index; i < i_current_index + i_indexes_to_go; i++)
	{
		if (i_column_index == this->i_m_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		xd_help[i_line_index][i_column_index] = pd_solution[i];
		i_column_index++;
	}
	i_current_index += i_indexes_to_go;


	i_line_index = 0;
	i_column_index = 0;
	i_indexes_to_go = this->i_m_size * this->i_s_size;
	for (int i = i_current_index; i < i_current_index + i_indexes_to_go; i++)
	{
		if (i_column_index == this->i_s_size)
		{
			i_column_index = 0;
			i_line_index++;
		}
		xd_help[i_line_index][i_column_index] = pd_solution[i];
		i_column_index++;
	}
	i_current_index += i_indexes_to_go;




	for (int i = 0; i < this->i_d_size; i++)
	{
		double xd_sum = 0;
		for (int j = 0; j < this->i_d_size; j++)
		{
			for (int k = 0; k < this->i_f_size; k++)
			{
				xd_sum += xd_help[j][k];
			}
		}
		if (xd_sum > this->sd_table[i])
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XD_SD_INTREVAL;
			return false;
		}
	}

	for (int i = 0; i < this->i_f_size; i++)
	{
		double xf_sum = 0;
		for (int j = 0; j < this->i_f_size; j++)
		{
			for (int k = 0; k < this->i_m_size; k++)
			{
				xf_sum += xf_help[j][k];
			}
		}
		if (xf_sum > this->sf_table[i])
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XF_SF_INTREVAL;
			return false;
		}
	}

	for (int i = 0; i < this->i_m_size; i++)
	{
		double xm_sum = 0;
		for (int j = 0; j < this->i_m_size; j++)
		{
			for (int k = 0; k < this->i_s_size; k++)
			{
				xm_sum += xm_help[j][k];
			}
		}
		if (xm_sum > this->sm_table[i])
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XM_SM_INTREVAL;
			return false;
		}
	}

	for (int i = 0; i < this->i_s_size; i++)
	{
		double xm_sum = 0;
		for (int j = 0; j < this->i_s_size; j++)
		{
			for (int k = 0; k < this->i_m_size; k++)
			{
				xm_sum += xm_help[j][k];
			}
		}
		if (xm_sum > this->ss_table[i])
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XM_SS_INTREVAL;
			return false;
		}
	}

	for (int i = 0; i < this->i_f_size; i++)
	{
		double xd_sum = 0;
		double xf_sum = 0;
		for (int j = 0; j < this->i_d_size; j++)
		{
			xd_sum += xd_help[j][i];
		}
		for (int k = 0; k < this->i_m_size; k++)
		{
			xf_sum += xf_help[i][k];
		}
		if (xd_sum < xf_sum)
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XD_XF_INTREVAL;
			return false;
		}
	}

	for (int i = 0; i < this->i_m_size; i++)
	{
		double xf_sum = 0;
		double xm_sum = 0;
		for (int j = 0; j < this->i_f_size; j++)
		{
			xf_sum += xf_help[j][i];
		}
		for (int k = 0; k < this->i_s_size; k++)
		{
			xm_sum += xm_help[i][k];
		}
		if (xf_sum < xm_sum)
		{
			this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
			this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
			this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
			*pi_error_num = I_ERROR_XF_XM_INTREVAL;
			return false;
		}
	}
	this->vDeleteTwoDementionalArray(xd_help, this->i_d_size);
	this->vDeleteTwoDementionalArray(xf_help, this->i_f_size);
	this->vDeleteTwoDementionalArray(xm_help, this->i_m_size);
	*pi_error_num = I_NO_ERROR;
	return true;
	
}

bool CMscnProblem::bIfIntervalCorrect()
{
	if (!(*this->b_if_set_pd_problem && *this->b_if_set_pd_solution))
	{
		return false;
	}
	else 
	{
		for (int i = 0; i < this->i_d_size; i++)
		{
			for (int j = 0; j < this->i_f_size; j++)
			{
				if (this->xd_min_max[i][j].first > this->xd_table[i][j] && this->xd_min_max[i][j].second < this->xd_table[i][j])
				{
					return false;
				}

			}
		}

		for (int i = 0; i < this->i_f_size; i++)
		{
			for (int j = 0; j < this->i_m_size; j++)
			{
				if (this->xf_min_max[i][j].first > this->xf_table[i][j] && this->xf_min_max[i][j].second < this->xf_table[i][j])
				{
					return false;
				}

			}
		}

		for (int i = 0; i < this->i_m_size; i++)
		{
			for (int j = 0; j < this->i_s_size; j++)
			{
				if (this->xm_min_max[i][j].first > this->xm_table[i][j] && this->xm_min_max[i][j].second < this->xm_table[i][j])
				{
					return false;
				}

			}
		}
		return true;
	}
}

void CMscnProblem::vGenerateInstance(int iInstanceSeed)
{
	/*






#define D_MAX_SD 50.0;
#define D_MAX_SF 50.0;
#define D_MAX_SM 50.0;
#define D_MAX_SS 50.0;








#define D_MIN_SD 1.0;
#define D_MIN_SF 1.0;
#define D_MIN_SM 1.0;
#define D_MIN_SS 1.0;
	*/
	if (*this->b_if_set_sizes)
	{
		CRandom* cR = new CRandom(iInstanceSeed);
		//cd double **
		double d_min = D_MIN_CD;
		double d_max = D_MAX_CD;
		this->generateForTwoDimentional(cR, this->cd_table, this->i_d_size, this->i_f_size, d_min, d_max);
		//cf double **
		d_min = D_MIN_CF; 
		d_max = D_MAX_CF;
		this->generateForTwoDimentional(cR, this->cf_table, this->i_f_size, this->i_m_size, d_min, d_max);
		//cm double **
		d_min = D_MIN_CM;
		d_max = D_MAX_CM;
		this->generateForTwoDimentional(cR, this->cm_table, this->i_m_size, this->i_s_size, d_min, d_max);
        //ud uf um double *
		d_min = D_MIN_UD;
		d_max = D_MAX_UD;
		this->generateForOneDimentional(cR, this->ud_table, this->i_d_size, d_min, d_max);

		d_min = D_MIN_UF;
		d_max = D_MAX_UF;
		this->generateForOneDimentional(cR, this->uf_table, this->i_f_size, d_min, d_max);

		d_min = D_MIN_UM;
		d_max = D_MAX_UM;
		this->generateForOneDimentional(cR, this->um_table, this->i_m_size, d_min, d_max);

        //sd sf sm ss double *
		d_min = D_MIN_SD;
		d_max = D_MAX_SD;
		this->generateForOneDimentional(cR, this->sd_table, this->i_d_size, d_min, d_max);

		d_min = D_MIN_SF;
		d_max = D_MAX_SF;
		this->generateForOneDimentional(cR, this->sf_table, this->i_f_size, d_min, d_max);

		d_min = D_MIN_SM;
		d_max = D_MAX_SM;
		this->generateForOneDimentional(cR, this->sm_table, this->i_m_size, d_min, d_max);

		d_min = D_MIN_SS;
		d_max = D_MAX_SS;
		this->generateForOneDimentional(cR, this->ss_table, this->i_s_size, d_min, d_max);
    

	}
}


