#include "CMscnProblem.h"
int main()
{
	{
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
	}
	system("pause");
	return 0;
}