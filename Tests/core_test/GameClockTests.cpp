#include "pch.h"
#include "CppUnitTest.h"
#include "udan/core/GameClock.h"
#include "udan/debug/Logger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(CoreTest)
	{
	public:

		void TestTargetFramerate(uint16_t target, int accuracy)
		{
			float acc = accuracy / 100.f;
			acc = 1 - acc;
			udan::core::GameClock gc(target);
			float totaltime = 0;
			float time = 0;
			uint32_t fps = 0;
			int low = (float)target * (1 - acc);
			int high = (float)target * (1 + acc);
			while (totaltime < 13.f)
			{
				const float deltaTime = gc.Tick();
				time += deltaTime;
				totaltime += deltaTime;
				fps++;
				if (time >= 1.f)
				{
					if (totaltime > 3.f)
					{
						if (fps < low || fps > high)
						{
							std::wstringstream wss;
							wss << "FPS : " << fps << std::endl;
							Assert::IsTrue(false, wss.str().c_str());
						}
					}
						
					fps = 0;
					time = 0.f;
				}
			}
		}
		
		TEST_METHOD(GameClock30)
		{
			TestTargetFramerate(30, 98);
		}

		TEST_METHOD(GameClock60)
		{
			TestTargetFramerate(60, 98);
		}

		TEST_METHOD(GameClock120)
		{
			TestTargetFramerate(120, 98);
		}

		TEST_METHOD(GameClock240)
		{
			TestTargetFramerate(240, 98);
		}

		TEST_METHOD(GameClock580)
		{
			TestTargetFramerate(580, 98);
		}
	};
}
