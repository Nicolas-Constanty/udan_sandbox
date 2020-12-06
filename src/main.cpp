// udan_sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application.h"

int main(int argc, char* argv[])
{
	Application application(argc, argv);
	application.Init(argc, argv);
	application.Run();
	return 0;
}
