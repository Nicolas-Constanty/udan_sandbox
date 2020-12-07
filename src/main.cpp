// udan_sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application.h"
#include "udan/utils/Task.h"
#include "udan/utils/ThreadPool.h"

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
	Sleep(sec * 1000);
}

int main(int argc, char* argv[])
{
	/*Application application(argc, argv);
	application.Init(argc, argv);
	application.Run();
	return 0;*/

	//std::thread consumers[10], producers[10];
	//// spawn 10 consumers and 10 producers:
	//for (int i = 0; i < 10; ++i) {
	//	consumers[i] = std::thread(consumer);
	//	producers[i] = std::thread(producer, i + 1);
	//}

	//// join them back:
	//for (int i = 0; i < 10; ++i) {
	//	producers[i].join();
	//	consumers[i].join();
	//}

	//Application application(argc, argv);

	udan::utils::DependencyTask *t1 = new udan::utils::DependencyTask([]() { print_task_id(1); });
	udan::utils::DependencyTask *t2 = new udan::utils::DependencyTask([]() { print_task_id(1); });//
	udan::utils::DependencyTask *t3 = new udan::utils::DependencyTask([]() { print_task_id(1); }, {}, udan::utils::TaskPriority::LOW);//, {&t1});
	udan::utils::DependencyTask *t4 = new udan::utils::DependencyTask([]() { print_task_id(1); }, {}, udan::utils::TaskPriority::HIGH);//, { &t3, &t2 });
	udan::utils::DependencyTask* t5 = new udan::utils::DependencyTask([]() { print_task_id(1); }, {}, udan::utils::TaskPriority::CRITICAL);//, { &t4 });
	udan::utils::DependencyTask *t6 = new udan::utils::DependencyTask([]() { print_task_id(1); });

	std::vector<udan::utils::ATask*> tasks;

	tasks.push_back(t1);
	tasks.push_back(t2);
	tasks.push_back(t3);
	tasks.push_back(t4);
	tasks.push_back(t5);
	tasks.push_back(t6);

	udan::utils::ThreadPool thread_pool(4);
	Sleep(1000);
	for (const auto& task: tasks)
	{
		thread_pool.Schedule(task);
	}
	Sleep(10000);
	thread_pool.Stop();
	return 0;
}
