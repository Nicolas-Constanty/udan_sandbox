// udan_sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "udan/core/Config.h"
#include "udan/debug/Logger.h"

int main(int argc, char* argv[])
{
	udan::debug::Logger::init();
	udan::core::Config config;
	udan::core::createConfig(argc, argv, &config);
	return 0;
}
