#include "CMscnProblem.h"
int main()
{
	{
		CMscnProblem cm = CMscnProblem();
		cout << cm.bGetIfGoodInit();
		cout << cm.bGetIfGoodPdSolution();
		cout << cm.bGetIfGoodSetValue();
		cm.vSetSizes(2, 3, 3, 5);
	}
	system("pause");
	return 0;
}