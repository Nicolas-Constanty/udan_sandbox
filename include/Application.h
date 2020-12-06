#pragma once

#include "udan/core/Application.h"

class Application : public udan::core::Application
{
public:
	Application(int argc, char* argv[]);
	~Application() override;
	void Init(int argc, char* argv[]) override;
};
