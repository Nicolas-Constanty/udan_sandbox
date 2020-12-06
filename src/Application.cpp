#include "Application.h"

Application::Application(int argc, char* argv[])
: udan::core::Application(argc, argv)
{
	
}

void Application::Init(int argc, char* argv[])
{
	int entityCount = 1000000;
	udan::ecs::EntityManager<udan::core::Entity> *em = GetEntityManager();
	udan::core::Entity lastEntity;
	for (int i = 0; i < entityCount; ++i)
	{
		if (i % 3 != 0)
		{
			lastEntity = em->CreateEntity();
		}
		else
		{
			em->CreateEntity();
			em->ReleaseEntity(lastEntity);
		}
	}
}

Application::~Application()
{
}
