#include "CMscnProblem.h"



CMscnProblem::CMscnProblem()
{
	this->b_if_good_init = new bool;

	this->b_if_good_pd_solution = new bool;
	this->b_if_was_set_value = new bool;
	*(this->b_if_good_init) = true;

	*(this->b_if_good_pd_solution) = true;
	*(this->b_if_was_set_value) = false;
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

	//delete another parametrs
	this->vDeleteOneDimensionalArray(this->ud_table);
	this->vDeleteOneDimensionalArray(this->uf_table);
	this->vDeleteOneDimensionalArray(this->um_table);
	this->vDeleteOneDimensionalArray(this->p_table);

	this->vDeleteTwoDementionalArray(this->xd_min_max, this->i_d_size);
	this->vDeleteTwoDementionalArray(this->xf_min_max, this->i_f_size);
	this->vDeleteTwoDementionalArray(this->xm_min_max, this->i_m_size);

	this->vDeleteTwoDementionalArray(this->xd_table, this->i_d_size);
	this->vDeleteTwoDementionalArray(this->xf_table, this->i_f_size);
	this->vDeleteTwoDementionalArray(this->xm_table, this->i_m_size);

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
			if (pp_pointer[i] == NULL) delete pp_pointer[i];
		}
		delete pp_pointer;
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

bool CMscnProblem::setValueCD(double d_value, int i_x_index, int i_y_index)
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

bool CMscnProblem::setValueCF(double d_value, int i_x_index, int i_y_index)
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

bool CMscnProblem::setValueCM(double d_value, int i_x_index, int i_y_index)
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

bool CMscnProblem::setValueSD(double d_value, int i_index)
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

bool CMscnProblem::setValueSF(double d_value, int i_index)
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

bool CMscnProblem::setValueSM(double d_value, int i_index)
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

bool CMscnProblem::setValueSS(double d_value, int i_index)
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