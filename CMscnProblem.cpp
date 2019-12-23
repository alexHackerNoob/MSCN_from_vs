#include "CMscnProblem.h"



CMscnProblem::CMscnProblem()
{
	*(this->b_if_good_init) = true;
	*(this->b_if_good_set_value) = true;
	*(this->b_if_good_pd_solution) = true;
}


CMscnProblem::~CMscnProblem()
{
	//delete one-dimentional double arrays
	this->vDeleteOneDimensionalArray(this->sd_table);
	this->vDeleteOneDimensionalArray(this->sf_table);
	this->vDeleteOneDimensionalArray(this->sm_table);
	this->vDeleteOneDimensionalArray(this->ss_table);
	//delete two-dimensional double arrays
	this->vDeleteTwoDementionalArray(this->cd_table, this->d_size);
	this->vDeleteTwoDementionalArray(this->cf_table, this->f_size);
	this->vDeleteTwoDementionalArray(this->cm_table,this->m_size);
	//delete bool pointers
	delete this->b_if_good_init;
	delete this->b_if_good_pd_solution;
	delete this->b_if_good_set_value;
}

void CMscnProblem::vSetSizeOfD(int d_size)
{
	if (d_size <= 0 || !this->b_if_good_init)
	{
		*(this->b_if_good_init) = false;
	}
	else 
	{
		this->d_size = d_size;
		this->cd_table = new double*[d_size];
		this->sd_table = new double[d_size];
	}
}

void CMscnProblem::vSetSizeOfF(int f_size)
{
	if (f_size <= 0 || !this->b_if_good_init)
	{
		*(this->b_if_good_init) = false;
	}
	else {
		this->f_size = f_size;
		for (int i = 0; i < this->d_size; i++)
		{
			this->cd_table[i] = new double[f_size];
		}
		this->cf_table = new double*[f_size];
		this->sf_table = new double[f_size];
	}
}

void CMscnProblem::vSetSizeOfM(int m_size)
{
	if (m_size <= 0 || !this->b_if_good_init)
	{
		*(this->b_if_good_init) = false;
	}
	else {
		this->m_size = m_size;
		for (int i = 0; i < this->f_size; i++)
		{
			this->cf_table[i] = new double[m_size];
		}
		this->cm_table = new double*[m_size];
		this->sm_table = new double[m_size];
	}
}

void CMscnProblem::vSetSizeOfS(int s_size)
{
	if (s_size <= 0 || !this->b_if_good_init)
	{
		*(this->b_if_good_init) = false;
	}
	else {
		this->s_size = s_size;
		for (int i = 0; i < this->m_size; i++)
		{
			this->cm_table[i] = new double[s_size];
		}
		this->ss_table = new double[s_size];
	}
}



void CMscnProblem::vDeleteOneDimensionalArray(double* pd_table)
{
	if (pd_table != nullptr) delete pd_table;
}

void CMscnProblem::vDeleteTwoDementionalArray(double** pd_table, int i_size)
{
	if (pd_table != nullptr)
	{
		for (int i = 0; i < i_size; i++)
		{
			if (pd_table[i] != NULL) delete pd_table[i];
		}
		delete pd_table;
	}
}

int CMscnProblem::vCopyTableOneD(int i_prev_size, int i_future_size, double * pd_table)
{
	if (pd_table == nullptr)
	{
		pd_table = new double[i_future_size];
	}
	else 
	{
		double *pd_table_help;
		int i_actual_size_copy_cicle = 0;
		if (i_prev_size <= i_future_size)
		{
			i_actual_size_copy_cicle = i_prev_size;
		}
		else
		{
			i_actual_size_copy_cicle = i_future_size;
		}
		pd_table_help = new double[i_future_size];
		for (int i = 0; i < i_actual_size_copy_cicle; i++)
		{
			if (pd_table[i] != NULL)
			{
				pd_table_help[i] = pd_table[i];
			}
		}
		this->vDeleteOneDimensionalArray(pd_table);
		pd_table = pd_table_help;
		pd_table_help = NULL;
		return i_future_size;
	}
}

int CMscnProblem::vCopyTableTwoD(int i_prev_size, int i_future_size, double ** pd_table)
{
	if (pd_table == nullptr)
	{
		pd_table = new double*[i_future_size];
	}
	double **pd_table_help;
	int i_actual_size_copy_cicle = 0;
	if (i_prev_size <= i_future_size)
	{
		i_actual_size_copy_cicle = i_prev_size;
	}
	else
	{
		i_actual_size_copy_cicle = i_future_size;
	}
	pd_table_help = new double*[i_future_size];
	for (int i = 0; i < i_actual_size_copy_cicle; i++)
	{
		//if table of null

		pd_table_help[i] = pd_table[i];
	}
	this->vDeleteTwoDementionalArray(pd_table, i_prev_size);
	pd_table = pd_table_help;
	pd_table_help = NULL;
	return i_future_size;
}

bool CMscnProblem::getIfGoodInit()
{
	return *(this->b_if_good_init);
}

bool CMscnProblem::getbIfGoodSetValue()
{
	return *(this->b_if_good_set_value);
}

bool CMscnProblem::getGoodPdSolution()
{
	return *(this->b_if_good_pd_solution);
}

void CMscnProblem::setSizes(int d_size, int f_size, int m_size, int s_size)
{
	this->vSetSizeOfD(d_size);
	this->vSetSizeOfF(f_size);
	this->vSetSizeOfM(m_size);
	this->vSetSizeOfS(s_size);
}

void CMscnProblem::setSizesSmart(int d_size, int f_size, int m_size, int s_size)
{
	if (this->cd_table == NULL || this->cf_table == NULL || this->cm_table == NULL || this->ss_table == NULL)
	{

	}
	else {
		//without replacing sizes
		this->vCopyTableOneD(this->d_size, d_size, this->sd_table);
		this->vCopyTableOneD(this->f_size, f_size, this->sf_table);
		this->vCopyTableOneD(this->m_size, m_size, this->sm_table);
		this->vCopyTableOneD(this->s_size, s_size, this->ss_table);
		//with replacing sizes
		this->vSetSmartSizeCd(d_size, f_size);
		this->vSetSmartSizeCf(f_size, m_size);
		this->vSetSmartSizeCm(m_size, s_size);
	}
}

void CMscnProblem::vSetSmartSizeCd(int d_size, int f_size)
{
	this->d_size = this->vCopyTableTwoD(this->d_size, d_size, this->cd_table);
	for (int i = 0; i < this->d_size; i++)
	{
		if (cd_table[i] != NULL)
		{
			this->vCopyTableOneD(this->f_size, f_size, cd_table[i]);
		}
		else
		{
			//if new size > old size
			cd_table[i] = new double[f_size];
		}
	}
}

void CMscnProblem::vSetSmartSizeCf(int f_size, int m_size)
{
	this->f_size = this->vCopyTableTwoD(this->f_size, f_size, this->cf_table);
	for (int i = 0; i < this->f_size; i++)
	{
		if (cd_table[i] != NULL)
		{
			this->vCopyTableOneD(this->m_size, m_size, cf_table[i]);
		}
		else
		{
			//if new size > old size
			cf_table[i] = new double[m_size];
		}
	}
}

void CMscnProblem::vSetSmartSizeCm(int m_size, int s_size)
{
	this->m_size = this->vCopyTableTwoD(this->m_size, m_size, this->cm_table);
	for (int i = 0; i < this->m_size; i++)
	{
		if (cm_table[i] != NULL)
		{
			this->vCopyTableOneD(this->s_size, s_size, cm_table[i]);
		}
		else
		{
			//if new size > old size
			cm_table[i] = new double[s_size];
		}
	}
	this->s_size = s_size;
}


void CMscnProblem::setValueOfCD(int i_index1, int i_index2, double value)
{
	if (i_index1 < 0 || i_index1 >= this->d_size || i_index2 < 0 || i_index2 >= this->f_size || !this->b_if_good_set_value || !this->b_if_good_init)
	{
		*(this->b_if_good_set_value) = false;
	}
	else 
	{
		this->cd_table[i_index1][i_index2] = value;
	}
}

void CMscnProblem::setValueOfCF(int i_index1, int i_index2, double value)
{
	if (i_index1 < 0 || i_index1 >= this->f_size || i_index2 < 0 || i_index2 >= this->m_size || !this->b_if_good_set_value || !this->b_if_good_init)
	{
		*(this->b_if_good_set_value) = false;
	}
	else
	{
		this->cf_table[i_index1][i_index2] = value;
	}
}

void CMscnProblem::setValueOfCM(int i_index1, int i_index2, double value)
{
	if (i_index1 < 0 || i_index1 >= this->m_size || i_index2 < 0 || i_index2 >= this->s_size || !this->b_if_good_set_value || !this->b_if_good_init)
	{
		*(this->b_if_good_set_value) = false;
	}
	else
	{
		this->cm_table[i_index1][i_index2] = value;
	}
}

bool CMscnProblem::vGetQuality(double * pd_solution, int i_size_pd_solution)
{
	return true;
}

