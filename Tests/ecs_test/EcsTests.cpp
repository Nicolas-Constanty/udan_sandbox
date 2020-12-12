#include "pch.h"
#include "CppUnitTest.h"
#include "udan/debug/Logger.h"
#include "udan/ecs/World.h"
#include "udan/utils/utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilsTest
{
	typedef uint32_t Entity;
	

	struct Pos
	{
		float x;
		float y;
		float z;
		explicit Pos(float x, float y, float z) : x(x), y(y), z(z) {}
	};

	struct Velocity
	{
		float dx;
		float dy;
		float dz;
		explicit Velocity(float x, float y, float z) : dx(x), dy(y), dz(z) {}
	};

	void PosSystem(Pos& pos, const Velocity& vel)
	{
		float deltaTime = 0.1f;
		pos.x += vel.dx * deltaTime;
		pos.y += vel.dy * deltaTime;
		pos.z += vel.dz * deltaTime;
	}

	//udan::ecs::EntityManager<Entity> *udan::ecs::EntityManager<Entity>::m_instance = nullptr;
	bool float_equals(float a, float b, float epsilon = 0.0001f)
	{
		return std::abs(a - b) < epsilon;
	}
	TEST_CLASS(EcsTest)
	{
	public:

		TEST_METHOD(EcsSimple)
		{
			const size_t entity_count = 1000;
			udan::ecs::EntityManager<Entity> manager(entity_count);
			udan::ecs::World<Entity> world(entity_count);
			const Entity e1 = world.CreateEntity();
			const Entity e2 = world.CreateEntity();
			world.PushComponents(e1, Pos{ 10.f, 20.f ,30.f }, Velocity{ 100.f, 100.f, 100.f });
			world.EmplaceComponent<Pos>(e2, 40.f, 50.f , 60.f);
			world.EmplaceComponent<Velocity>(e2, 200.f, 200.f, 200.f);
			world.AddSystemLambdas<Pos&, const Velocity &>(
				[](Pos& pos, const Velocity& vel)
				{
					pos.x *= vel.dx;
					pos.y *= vel.dy;
					pos.z *= vel.dz;
				}
			);
			world.Update();
			const auto& pos1 = world.GetEntityComponent<Pos>(e1);
			Assert::IsTrue(float_equals(pos1.x, 1000.f));
			Assert::IsTrue(float_equals(pos1.y, 2000.f));
			Assert::IsTrue(float_equals(pos1.z, 3000.f));
			
			const auto& pos2 = world.GetEntityComponent<Pos>(e2);
			Assert::IsTrue(float_equals(pos2.x, 8000.f));
			Assert::IsTrue(float_equals(pos2.y, 10000.f));
			Assert::IsTrue(float_equals(pos2.z, 12000.f));
		}

		TEST_METHOD(Ecs_10000)
		{
			const size_t entity_count = 100000;
			udan::ecs::EntityManager<Entity> manager(entity_count);
			udan::ecs::World<Entity> world(entity_count);
			for (auto i = 0; i < entity_count; ++i) {
				const Entity entity = world.CreateEntity();
				world.EmplaceComponent<Pos>(entity, i * 1.f, i * 1.f, i * 1.f);
				if (i % 2 == 0) { world.EmplaceComponent<Velocity>(entity, i * .1f, i * .1f, i * .1f); }
			}
			float deltaTime = 0.1f;
			world.AddSystemLambdas<Pos&, const Velocity &>(
				[&](Pos &pos, const Velocity &vel)
				{
					pos.x += vel.dx * deltaTime;
					pos.y += vel.dy * deltaTime;
					pos.z += vel.dz * deltaTime;
				}
			);
			{
				const udan::utils::Timer timer;
				world.Update();
				const auto execTime = timer.GetDeltaTime();
				Logger::WriteMessage(fmt::format("Time: (fps {}) {}s", 1.0 / execTime, execTime).data());
			}
		}

		TEST_METHOD(Ecs_10000_func)
		{
			const size_t entity_count = 100000;
			udan::ecs::EntityManager<Entity> manager(entity_count);
			udan::ecs::World<Entity> world(entity_count);
			for (auto i = 0; i < entity_count; ++i) {
				const Entity entity = world.CreateEntity();
				world.EmplaceComponent<Pos>(entity, i * 1.f, i * 1.f, i * 1.f);
				if (i % 2 == 0) { world.EmplaceComponent<Velocity>(entity, i * .1f, i * .1f, i * .1f); }
			}
			float deltaTime = 0.1f;
			world.AddSystem<Pos&, const Velocity&>(
				&PosSystem
			);
			{
				const udan::utils::Timer timer;
				world.Update();
				const auto execTime = timer.GetDeltaTime();
				Logger::WriteMessage(fmt::format("Time: (fps {}) {}s", 1.0 / execTime, execTime).data());
			}
		}
	};
}
