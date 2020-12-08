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
	//Sleep(sec * 1000);
}

int main(int argc, char* argv[])
{
	Application application(argc, argv);
	application.Init(argc, argv);
	application.Run();
	return 0;
}
