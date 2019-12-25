#include "CMscnProblem.h"
int main()
{
	{
		/*
		CMscnProblem cm = CMscnProblem();
		cout << cm.bGetIfGoodInit();
		cout << cm.bGetIfGoodPdSolution();
		cm.vSetSizes(2, 3, 3, 5);
		CMscnProblem cm1 = CMscnProblem();
		cout << cm1.bGetIfGoodInit();
		cm.vSetSizes(-3, -3, -5, 6);
		cout << cm1.bGetIfGoodPdSolution();
		cm1.vSetSizes(-1, -2, -3, -4);
		cout << cm1.bGetIfGoodInit();
		cout << cm1.bGetIfGoodPdSolution();
		cm1.vSetSizes(1, 2, 3, 4);
		cout << endl << "------------------------------------------------------------" << endl;
		cout << cm1.bsetValueCD(1, 0, 0) << endl;
		cout << cm.bsetValueCD(1, 0, 0) << endl;
		cout << cm.bsetValueCF(1, 0, 0) << endl;

		cout << cm1.bsetValueSD(1, 0) << endl;
		cout << cm.bsetValueSF(1, 0) << endl;
		std::pair<double, double>** xd_min_max = new std::pair<double, double>*[5];
		for (int i = 0; i < 5; i++)
		{
			xd_min_max[i] = new std::pair<double, double>;
		}
		xd_min_max[0][0].first = 1;
		xd_min_max[0][0].second = 1;
		cout << "------------------" <<endl<< xd_min_max[0][0].first<<endl;
		cout << "------------------" <<endl<< xd_min_max[0][0].second<< endl;
		xd_min_max[0][0].first = 8;
		xd_min_max[0][0].second = 8.6;
		cout << "------------------" << endl << xd_min_max[0][0].first << endl;
		cout << "------------------" << endl << xd_min_max[0][0].second << endl;

		for (int i = 0; i < 5; i++)
		{
			delete xd_min_max[i];
		}
		delete xd_min_max;
		*/
		double *pd_problem = new double[21];
		pd_problem[0] = 1;
		pd_problem[1] = 1;
		pd_problem[2] = 1;
		pd_problem[3] = 1;
		pd_problem[4] = 100;
		pd_problem[5] = 50;
		pd_problem[6] = 10.5;
		pd_problem[7] = 100;
		pd_problem[8] = 3;
		pd_problem[9] = 4;
		pd_problem[10] = 1;
		pd_problem[11] = 10;
		pd_problem[12] = 10;
		pd_problem[13] = 100;
		pd_problem[14] = 300.5;
		pd_problem[15] = 1;
		pd_problem[16] = 100;
		pd_problem[17] = 1;
		pd_problem[18] = 100;
		pd_problem[19] = 1;
		pd_problem[20] = 100;
		CMscnProblem cm = CMscnProblem();
		cm.bGetDatasFromProblem(pd_problem, 20);
		delete pd_problem;

	}
	system("pause");
	return 0;
}