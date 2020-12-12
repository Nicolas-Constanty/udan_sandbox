#include "pch.h"
#include "CppUnitTest.h"
#include "udan/debug/Logger.h"
#include "udan/utils/Event.h"
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
			
			const auto t1 = std::make_shared<udan::utils::Task>([&m_results]() { m_results[0] = 1; });
			const auto t2 = std::make_shared<udan::utils::Task>([&m_results]() { m_results[1] = 4; });
			const auto t3 = std::make_shared<udan::utils::Task>([&m_results]() { m_results[2] = 9; });
			const auto t4 = std::make_shared<udan::utils::Task>([&m_results]() { m_results[3] = 16; });

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
			m_results.reserve(5);
			udan::utils::ThreadPool thread_pool(1);

			const auto t1 = std::make_shared<udan::utils::Task>([&m_results]() { m_results.emplace_back(1); }, udan::utils::TaskPriority::NORMAL);
			const auto t2 = std::make_shared<udan::utils::Task>([&m_results]() { m_results.emplace_back(0); }, udan::utils::TaskPriority::LOW);
			const auto t3 = std::make_shared<udan::utils::Task>([&m_results]() { m_results.emplace_back(2); }, udan::utils::TaskPriority::HIGH);
			const auto t4 = std::make_shared<udan::utils::Task>([&m_results]() { m_results.emplace_back(1); }, udan::utils::TaskPriority::NORMAL);
			const auto t5 = std::make_shared<udan::utils::Task>([&m_results]() { m_results.emplace_back(3); }, udan::utils::TaskPriority::CRITICAL);

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
			m_results.reserve(5);
			m_results.emplace_back(0);
			m_results.emplace_back(0);
			m_results.emplace_back(0);
			m_results.emplace_back(0);
			m_results.emplace_back(0);

			udan::utils::ThreadPool thread_pool(4);

			const auto t1 = std::make_shared<udan::utils::DependencyTask>([&m_results]() { m_results[0] = 3; });
			const auto t2 = std::make_shared<udan::utils::DependencyTask>([&m_results]() { m_results[1] = 5; });
			const auto t3 = std::make_shared<udan::utils::DependencyTask>([&m_results]() { m_results[2] = m_results[0] * m_results[0]; }, udan::utils::DependencyVector{t1});
			const auto t4 = std::make_shared<udan::utils::DependencyTask>([&m_results]() { m_results[3] = m_results[2] * m_results[1]; }, udan::utils::DependencyVector{t3, t2});
			const auto t5 = std::make_shared<udan::utils::DependencyTask>([&m_results]() { m_results[4] = 42; });

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

		int m_resultsEvent[4] = {0,0,0,0};

		void AssertResult(int count)
		{
			Assert::IsTrue(m_resultsEvent[count] == count);
		}
		TEST_METHOD(EventRegister)
		{
			udan::utils::Event<int> on_count;

			on_count += [this](int count) { m_resultsEvent[count] = count; };
			on_count.Register([this](int value) { AssertResult(value); });
			
			for (int i = 0; i < 4; ++i)
			{
				on_count.Invoke(i);
			}
		}
	};
}
