// udan_sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>

#include "Application.h"
#include "udan/ecs/World.h"
#include "udan/utils/utils.h"

//std::mutex mtx;
//std::condition_variable produce, consume;
//
//int cargo = 0;     // shared value by producers and consumers
//
//void consumer() {
//	std::unique_lock<std::mutex> lck(mtx);
//	while (cargo == 0) consume.wait(lck);
//	std::cout << cargo << '\n';
//	cargo = 0;
//	produce.notify_one();
//}
//
//void producer(int id) {
//	std::unique_lock<std::mutex> lck(mtx);
//	while (cargo != 0) produce.wait(lck);
//	cargo = id;
//	consume.notify_one();
//}



//class task
//{
//	int m_name;
//	std::mutex m_mtx;
//	std::condition_variable m_cv;
//	bool m_completed = false;
//	std::vector<task*> m_dependencies;
//
//public:
//	task(int name, const std::vector<task*>& tasks)
//	{
//		m_name = name;
//		for (const auto &task: tasks)
//		{
//			if (task == this)
//				continue;
//			m_dependencies.push_back(task);
//		}
//	}
//
//	int Name() const
//	{
//		return m_name;
//	}
//
//	void Exec()
//	{
//		std::unique_lock<std::mutex> lck(m_mtx);
//		std::cout << m_name << std::endl;
//		m_completed = true;
//		m_cv.notify_all();
//	}
//
//	const std::vector<task*> &GetDependencies() const
//	{
//		return m_dependencies;
//	}
//
//	bool Complited() const
//	{
//		return m_completed;
//	}
//
//	void WaitUntilComplited(std::unique_lock<std::mutex> &lock)
//	{
//		m_cv.wait(lock);
//	}
//
//	std::mutex &AquireMutex()
//	{
//		return m_mtx;
//	}
//};
//
//
//void execTask(task* t)
//{
//	const auto& dependencies = t->GetDependencies();
//	if (!dependencies.empty())
//	{
//		for (const auto &dependency : dependencies)
//		{
//			std::unique_lock<std::mutex> lck(dependency->AquireMutex());
//			while (!dependency->Complited())
//			{
//				dependency->WaitUntilComplited(lck);
//			}
//		}
//	}
//	t->Exec();
//};

void print_task_id(int sec)
{
	//Sleep(sec * 1000);
}

typedef uint32_t Entity;

struct Pos
{
	float x;
	float y;
	float z;
	Pos() : x(0), y(0), z(0) {};
	explicit Pos(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Velocity
{
	float dx;
	float dy;
	float dz;
	Velocity() : dx(0), dy(0), dz(0) {};
	explicit Velocity(float x, float y, float z) : dx(x), dy(y), dz(z) {}
};

FORCEINLINE void SystemPos(Pos& pos, const Velocity& vel)
{
	float deltaTime = 0.1f;
	pos.x += vel.dx * deltaTime;
	pos.y += vel.dy * deltaTime;
	pos.z += vel.dz * deltaTime;
};

template<typename T1, typename T2>
class TestIteratif
{
public:
	TestIteratif(size_t capacity)
	{
		positions.reserve(capacity);
		velocities.reserve(capacity);
	}
	std::vector<T1>& get_positions() { return positions; }
	std::vector<T2>& get_velocities() { return velocities;  }
private:
	std::vector<T1> positions;
	std::vector<T2> velocities;
};

template<typename T1, typename T2>
void RunSystem(const std::function<void(T1, T2)>& func, int size, std::vector<Pos> &pos, std::vector<Velocity> &vel)
{
	for (int i = 0; i < size; ++i)
	{
		func(pos[i], vel[i]);
	}
}

void RunSystem1(int size, std::vector<Pos>& pos, const std::vector<Velocity>& vel)
{
	float deltaTime = 0.1f;
	for (int i = 0; i < size; ++i)
	{
		Pos& p = pos[i];
		const Velocity &v = vel[i];
		p.x += v.dx * deltaTime;
		p.y += v.dy * deltaTime;
		p.z += v.dz * deltaTime;
		Sleep(200);
	}
}



void *operator new(size_t size)
{
	//std::cout << "Allocate " << size << " bytes" << std::endl;
	return malloc(size);
}

int main(int argc, char* argv[])
{
	const size_t entity_count = 50000;
	udan::debug::Logger::Instance()->set_level(spdlog::level::info);
	std::tuple<Pos,Velocity> c = {};
	auto system = [&](Pos& pos, const Velocity& vel)
	{
		float deltaTime = 0.1f;
		pos.x += vel.dx * deltaTime;
		pos.y += vel.dy * deltaTime;
		pos.z += vel.dz * deltaTime;
	};
	
	//std::unique_ptr<TestIteratif<Pos, Velocity>> storage = std::make_unique<TestIteratif<Pos,Velocity>>(entity_count);
	//std::vector<std::unique_ptr<udan::utils::SparseSet<Entity>>> m_cache;
	//m_cache.push_back(std::make_unique<udan::utils::DataSet<Entity, Pos>>(entity_count));
	//m_cache.push_back(std::make_unique<udan::utils::DataSet<Entity, Velocity>>(entity_count));
	//{
	//	const udan::utils::Timer timer;
	//	udan::utils::DataSet<Entity, Pos>& pos = static_cast<udan::utils::DataSet<Entity, Pos>&>(*m_cache[0]);
	//	udan::utils::DataSet<Entity, Velocity>& vel = static_cast<udan::utils::DataSet<Entity, Velocity>&>(*m_cache[1]);
	//	for (auto i = 0; i < entity_count; ++i) {
	//		const float val = i * 1.f;
	//		pos.EmplaceBack(i, val, val, val);
	//		vel.EmplaceBack(i, val, val, val);
	//	}
	//	const auto execTime = timer.GetDeltaTime();
	//	std::cout << fmt::format("Iterative Time: (fps {}) {}s", 1.0 / execTime, execTime) << std::endl;
	//}
	//{
	//	const udan::utils::Timer timer;
	//	std::vector<Pos>& pos = static_cast<udan::utils::DataSet<Entity, Pos>&>(*m_cache[0]).GetData();
	//	std::vector<Velocity>& vel = static_cast<udan::utils::DataSet<Entity, Velocity>&>(*m_cache[1]).GetData();
	//	RunSystem<Pos&, const Velocity&>(system, entity_count, pos, vel);

	//	const auto execTime = timer.GetDeltaTime();
	//	std::cout << fmt::format("Iterative Time: (fps {}) {}s", 1.0 / execTime, execTime) << std::endl;
	//}

	udan::ecs::EntityManager<Entity> manager(entity_count);
	udan::ecs::World<Entity> world(entity_count);
	
	{
		const udan::utils::Timer timer;
		bool init = false;
		auto& pos = world.InitDataStorage<Pos>();
		auto& vel = world.InitDataStorage<Velocity>();
		for (auto i = 0; i < entity_count; ++i) {
			const Entity entity = world.CreateEntity();
			const float val = i * 1.f;
			pos.EmplaceBack(entity, val, val, val);
			vel.EmplaceBack(entity, val, val, val);
		}
		const auto execTime = timer.GetDeltaTime();
		std::cout << fmt::format("ECS Time: (fps {}) {}s", 1.0 / execTime, execTime) << std::endl;
	}

	world.AddMtSystem<Pos&, const Velocity&>(
		&SystemPos
		);
	{
		size_t iteration = 120;
		const udan::utils::Timer timer;
		for (int i = 0; i < iteration; ++i)
		{
			world.Update();
		}
		const auto execTime = timer.GetDeltaTime() / (double)iteration;
		std::cout << fmt::format("ECS Time: (fps {}) {}s", 1.0 / execTime, execTime) << std::endl;
	}
	/*Application application(argc, argv);
	application.Init(argc, argv);
	application.Run();*/
	return 0;
}
