#include "CMscnProblem.h"
int main()
{
	{
		CMscnProblem cm = CMscnProblem();
		cout << cm.bGetIfGoodInit();
		cout << cm.bGetIfGoodPdSolution();
		cout << cm.bGetIfGoodSetValue();
		cm.vSetSizes(2, 3, 3, 5);
		CMscnProblem cm1 = CMscnProblem();
		cout << cm1.bGetIfGoodInit();
		cm.vSetSizes(-3, -3, -5, 6);
		cout << cm1.bGetIfGoodPdSolution();
		cout << cm1.bGetIfGoodSetValue();
		cm1.vSetSizes(-1, -2, -3, -4);
		cout << cm1.bGetIfGoodInit();
		cout << cm1.bGetIfGoodPdSolution();
		cm1.vSetSizes(1, 2, 3, 4);
		cout << cm1.bGetIfGoodSetValue();
	}
	system("pause");
	return 0;
}