#include "ReadPdProblem.h"


#include <stdlib.h>


ReadPdProblem::ReadPdProblem(string s_file_name)
{
	this->s_file_name = s_file_name;
	this->i_pd_double_size = 0;
}


ReadPdProblem::~ReadPdProblem()
{
	if (this->pd_problem != NULL) delete this->pd_problem;
}

void ReadPdProblem::v_read_from_file()
{
	std::vector<string> vector_to_rem(0);
	vector_to_rem.push_back("\n");
	vector_to_rem.push_back("D");
	vector_to_rem.push_back("F");
	vector_to_rem.push_back("M");
	vector_to_rem.push_back("S");
	vector_to_rem.push_back("sd");
	vector_to_rem.push_back("sf");
	vector_to_rem.push_back("sm");
	vector_to_rem.push_back("ss");
	vector_to_rem.push_back("cd");
	vector_to_rem.push_back("cf");
	vector_to_rem.push_back("cm");
	vector_to_rem.push_back("ud");
	vector_to_rem.push_back("uf");
	vector_to_rem.push_back("um");
	vector_to_rem.push_back("p");
	vector_to_rem.push_back("xdminmax");
	vector_to_rem.push_back("xfminmax");
	vector_to_rem.push_back("xmminmax");
	//make array of lines
	char str[128];
	std::vector<string> vector_unuse_condition_of_elements(0);
	if ((this->pf_file = fopen(this->s_file_name.c_str(), "r")) == NULL) {
		printf("Cannot open file.\n");
		//exit(1);
	}
	else {
		while (!feof(this->pf_file))
		{
			if (fgets(str, 10, this->pf_file))
				vector_unuse_condition_of_elements.push_back(str);
		}
		//delete unnessersary symbols without " "
		for (int i = 0; i < vector_unuse_condition_of_elements.size(); i++)
		{
			for (int j = 0; j < vector_to_rem.size(); j++)
			{
				string s_to_rem = vector_to_rem[j];
				int i_first = vector_unuse_condition_of_elements[i].find(s_to_rem);
				if (i_first != string::npos)
				{
					vector_unuse_condition_of_elements[i].erase(i_first, i_first + vector_to_rem[j].size());
				}
			}
		}
		//delete 4 first " "

		for (int i = 0; i < 4; i++)
		{
			vector_unuse_condition_of_elements[i].erase(0, 1);
		}
		//make pre-finished vector(finished but string)
		int i_current_index_pre_finish_alloc = -1;
		std::vector<string> vector_pre_finish(0);
		for (int i = 0; i < vector_unuse_condition_of_elements.size(); i++)
		{
			if (vector_unuse_condition_of_elements[i] != "" && vector_unuse_condition_of_elements[i] != " ")
			{
				string s_to_separate = " ";
				int i_to_separete_index = vector_unuse_condition_of_elements[i].find(s_to_separate);
				vector_pre_finish.push_back("");
				i_current_index_pre_finish_alloc++;
				if (i_to_separete_index != string::npos)
				{
					for (int j = 0; j < vector_unuse_condition_of_elements[i].size(); j++)
					{
						if (vector_unuse_condition_of_elements[i][j] == s_to_separate[0])
						{
							vector_pre_finish.push_back("");
							i_current_index_pre_finish_alloc++;
						}
						else
						{
							vector_pre_finish[i_current_index_pre_finish_alloc] += vector_unuse_condition_of_elements[i][j];
						}
					}
				}
				else
				{
					vector_pre_finish[i_current_index_pre_finish_alloc] = vector_unuse_condition_of_elements[i];
				}
			}
		}
		fclose(this->pf_file);
		//create pd_problem (redefine type)
		vector_pre_finish = vDeleteUnnesesaryElements(vector_pre_finish);
		this->pd_problem = new double[vector_pre_finish.size()];
		this->i_pd_double_size = vector_pre_finish.size();
		for (int i = 0; i < vector_pre_finish.size(); i++)
		{
			double d_element = stod(vector_pre_finish[i].c_str());
			this->pd_problem[i] = d_element;
		}
	}
}

void ReadPdProblem::v_print_pd_problem()
{
	this->v_print_pd_table(this->pd_problem, i_pd_double_size);
}

double *ReadPdProblem::dGetPdProblem()
{
	return this->pd_problem;
}

int ReadPdProblem::iGetPdDoubleSize()
{
	return this->i_pd_double_size ;
}

void ReadPdProblem::v_print_pd_table(double * pd_table, int i_size)
{
	cout << endl;
	if (pd_table != NULL)
		for (int i = 0; i < i_size; i++)
			cout << *(pd_table + i) << endl;
}

std::vector<string> ReadPdProblem::vDeleteUnnesesaryElements(std::vector<string> vector)
{
	std::vector<string> v_to_return;
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] != "" && vector[i] != " " && vector[i] != "0")
		{
			v_to_return.push_back(vector[i]);
		}
	}
	return v_to_return;
}
