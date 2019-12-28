#pragma once
using namespace std;
#include "CMscnProblem.h"
#include <iostream>
#include <vector>
#include <string>
#pragma warning(disable:4996)

class WritePdProblem
{
	FILE* pf_file;
private:
	string s_file_name;
	int i_pd_double_size;
public:
	WritePdProblem(CMscnProblem cMP,string s_file_name);
	~WritePdProblem();
};

