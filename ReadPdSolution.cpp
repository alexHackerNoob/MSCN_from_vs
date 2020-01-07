#include "ReadPdSolution.h"





void ReadPdSolution::vPrintPdTable(double * pd_table, int i_size)
{
	if (pd_table != NULL)
		for (int i = 0; i < i_size; i++)
			cout << *(pd_table + i) << endl;
}

ReadPdSolution::ReadPdSolution(string s_file_name)
{
	this->s_file_name = s_file_name;
	this->i_pd_double_size = 0;
}

ReadPdSolution::~ReadPdSolution()
{
	if (this->pd_solution != NULL) delete this->pd_solution;
}

void ReadPdSolution::vReadFromFile()
{
	std::vector<string> vector_to_rem(0);
	vector_to_rem.push_back("\n");
	vector_to_rem.push_back("D");
	vector_to_rem.push_back("F");
	vector_to_rem.push_back("M");
	vector_to_rem.push_back("S");
	vector_to_rem.push_back("xd");
	vector_to_rem.push_back("xf");
	vector_to_rem.push_back("xm");
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
			if (vector_unuse_condition_of_elements[i] != "")
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
		this->pd_solution = new double[vector_pre_finish.size()];
		this->i_pd_double_size = vector_pre_finish.size();
		for (int i = 0; i < vector_pre_finish.size(); i++)
		{
			double d_element = stod(vector_pre_finish[i].c_str());
			this->pd_solution[i] = d_element;
		}
	}
}

void ReadPdSolution::vPrintPdSolution()
{
	this->vPrintPdTable(this->pd_solution, this->i_pd_double_size);
}

double * ReadPdSolution::dGetPdSolution()
{
	return this->pd_solution;
}

int ReadPdSolution::iGetPdDoubleSize()
{
	return this->i_pd_double_size;
}
