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
		cout << cm1.setValueCD(1, 0, 0) << endl;
		cout << cm.setValueCD(1, 0, 0) << endl;
		cout << cm.setValueCF(1, 0, 0) << endl;

		cout << cm1.setValueSD(1, 0) << endl;
		cout << cm.setValueSF(1, 0) << endl;
	}
	system("pause");
	return 0;
}