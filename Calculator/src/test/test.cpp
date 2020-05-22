#ifdef TEST

#include "ButtonModel.test.h"
#include "math_ext.test.h"

namespace ii887522::Calculator
{
	static void testButtonModel()
	{
		const ButtonModelTest buttonModelTest;
		buttonModelTest.testReactMouseMotion();
		buttonModelTest.testReactLeftMouseButtonDown();
		buttonModelTest.testReactLeftMouseButtonUp();
		buttonModelTest.testReactMouseLeaveWindow();
	}

	static int main()
	{
		testMathExt();
		testButtonModel();
		return 0;
	}
}

int main()
{
	return ii887522::Calculator::main();
}

#endif