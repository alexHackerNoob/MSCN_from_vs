#include "CMscnProblem.h"

#include <string> 

CMscnProblem::CMscnProblem()
{
	this->b_if_good_init = new bool;
	this->b_if_set_pd_problem = new bool;
	this->b_if_good_pd_solution = new bool;
	this->b_if_was_set_value = new bool;
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
		cout << "bad init (double **)pd_table";
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
			//delete two-dimensional double arrays
			this->vDeleteTwoDementionalArray(this->cd_table, this->i_d_size);
			this->vDeleteTwoDementionalArray(this->cf_table, this->i_f_size);
			this->vDeleteTwoDementionalArray(this->cm_table, this->i_m_size);
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
		*pd_mistake = D_MISTAKE_NOT_EXIST_PD_PROBLEM;
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
			*pd_mistake = D_NO_NISTAKE;
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
				d_k_u += d_sum_xf_m * this->uf_table[i];
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
				d_k_u += d_sum_xm_s * this->um_table[i];
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

	for (int i = 0; i < this->i_f_size; i++)
	{
		s_to_write += this->sf_table[i];
		if (i != this->i_f_size) s_to_write += " ";
	}

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


	if (file != NULL) // если есть доступ к файлу,
	{
		// инициализируем строку
		bool result = fputs(s_to_write.c_str(), file); // и записываем ее в файл
		if (!result) // если запись произошла успешно
			cout << "no mistakes in open file and put in " << endl; // выводим сообщение
	}
	else
		cout << "nistakes in open file";
	fclose(file);
	
	return true;
}


