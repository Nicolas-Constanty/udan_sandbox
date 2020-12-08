#include "pch.h"
#include "CppUnitTest.h"
#include "udan/debug/Logger.h"
#include "udan/utils/ThreadPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilsTest
{
	TEST_CLASS(UtilsTest)
	{
	public:
		TEST_METHOD(ThreadpoolSimple)
		{
			int m_results[4];
			
			udan::utils::ThreadPool thread_pool(4);
			
			udan::utils::Task* t1 = new udan::utils::Task([&m_results]() { m_results[0] = 1; });
			udan::utils::Task* t2 = new udan::utils::Task([&m_results]() { m_results[1] = 4; });
			udan::utils::Task* t3 = new udan::utils::Task([&m_results]() { m_results[2] = 9; });
			udan::utils::Task* t4 = new udan::utils::Task([&m_results]() { m_results[3] = 16; });

			thread_pool.Schedule(t1);
			thread_pool.Schedule(t2);
			thread_pool.Schedule(t3);
			thread_pool.Schedule(t4);
			
			thread_pool.StopWhenQueueEmpty(); //Synchronize with main thread and stop the thread queue

			Assert::IsTrue(m_results[0] == 1);
			Assert::IsTrue(m_results[1] == 4);
			Assert::IsTrue(m_results[2] == 9);
			Assert::IsTrue(m_results[3] == 16);
		}


		TEST_METHOD(ThreadpoolPriority)
		{
			std::vector<int> m_results;

			udan::utils::ThreadPool thread_pool(1);

			udan::utils::Task* t1 = new udan::utils::Task([&m_results]() { m_results.push_back(1); }, udan::utils::TaskPriority::NORMAL);
			udan::utils::Task* t2 = new udan::utils::Task([&m_results]() { m_results.push_back(0); }, udan::utils::TaskPriority::LOW);
			udan::utils::Task* t3 = new udan::utils::Task([&m_results]() { m_results.push_back(2); }, udan::utils::TaskPriority::HIGH);
			udan::utils::Task* t4 = new udan::utils::Task([&m_results]() { m_results.push_back(1); }, udan::utils::TaskPriority::NORMAL);
			udan::utils::Task* t5 = new udan::utils::Task([&m_results]() { m_results.push_back(3); }, udan::utils::TaskPriority::CRITICAL);

			thread_pool.Schedule(t1);
			thread_pool.Schedule(t2);
			thread_pool.Schedule(t3);
			thread_pool.Schedule(t4);
			thread_pool.Schedule(t5);

			thread_pool.StopWhenQueueEmpty(); //Synchronize with main thread and stop the thread queue

			Assert::IsTrue(m_results[0] == 3);
			Assert::IsTrue(m_results[1] == 2);
			Assert::IsTrue(m_results[2] == 1);
			Assert::IsTrue(m_results[3] == 1);
			Assert::IsTrue(m_results[4] == 0);
		}

		TEST_METHOD(ThreadpoolDependency)
		{
			std::vector<int> m_results;
			m_results.push_back(0);
			m_results.push_back(0);
			m_results.push_back(0);
			m_results.push_back(0);
			m_results.push_back(0);

			udan::utils::ThreadPool thread_pool(4);

			udan::utils::DependencyTask* t1 = new udan::utils::DependencyTask([&m_results]() { m_results[0] = 3; });
			udan::utils::DependencyTask* t2 = new udan::utils::DependencyTask([&m_results]() { m_results[1] = 5; });
			udan::utils::DependencyTask* t3 = new udan::utils::DependencyTask([&m_results]() { m_results[2] = m_results[0] * m_results[0]; }, {t1});
			udan::utils::DependencyTask* t4 = new udan::utils::DependencyTask([&m_results]() { m_results[3] = m_results[2] * m_results[1]; }, {t3, t2});
			udan::utils::DependencyTask* t5 = new udan::utils::DependencyTask([&m_results]() { m_results[4] = 42; });

			thread_pool.Schedule(t1);
			thread_pool.Schedule(t2);
			thread_pool.Schedule(t3);
			thread_pool.Schedule(t4);
			thread_pool.Schedule(t5);

			thread_pool.StopWhenQueueEmpty(); //Synchronize with main thread and stop the thread queue

			Assert::IsTrue(m_results[0] == 3);
			Assert::IsTrue(m_results[1] == 5);
			Assert::IsTrue(m_results[2] == 9);
			Assert::IsTrue(m_results[3] == 45);
			Assert::IsTrue(m_results[4] == 42);
		}
	};
}
