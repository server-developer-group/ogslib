#include "stdafx.h"
#include <UnitTest++.h>
#include "TestReporterStdout.h"

#include "testTime.h"
#include "testStream.h"


int _tmain(int argc, _TCHAR* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	UnitTest::RunAllTests();

	getchar();
	return 0;
}