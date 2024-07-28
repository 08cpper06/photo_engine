#include "Core/ThreadManager.hpp"


ThreadManager::~ThreadManager()
{
	Terminate();
}

ThreadManager* ThreadManager::Get()
{
	static ThreadManager Instance;
	return &Instance;
}

void ThreadManager::AddNewThread(EExecuteThreadType InType, std::function<void(EExecuteThreadType)> InMain)
{
	ThreadPool.emplace_back([InType, InMain]() { InMain(InType); });
}

bool ThreadManager::IsRequestTerminate() const
{
	return IsRequestEnd;
}

bool ThreadManager::Init()
{
	return true;
}
void ThreadManager::Terminate()
{
	for (;TaskList.size();)
	{
		std::this_thread::yield();
	}

	IsRequestEnd = true;
	for (std::thread& Thread : ThreadPool)
	{
		Thread.join();
	}
	ThreadPool.clear();
}

void ThreadManager::InternalExecute(EExecuteThreadType InType)
{
	while (!IsRequestEnd)
	{
		TAsyncTask Task;
		{
			std::lock_guard<std::mutex> locker(TaskListLocker);
			if (TaskList.size())
			{
				auto Itr = --TaskList.end();
				for (;;)
				{
					if (Itr == TaskList.begin())
					{
						Itr = Itr->Type == InType ? Itr : TaskList.end();
						break;
					}
					if (Itr->Type == InType)
					{
						break;
					}
					--Itr;
				}
				if (Itr != TaskList.end())
				{
					Task = std::move(*Itr);
					TaskList.erase(Itr);
				}
			}
		}
		Task();
		std::this_thread::yield();
	}
}

void ThreadManager::TaskNew(TAsyncTask&& InTask)
{
	std::lock_guard<std::mutex> locker(TaskListLocker);
	TaskList.push_back(std::move(InTask));
}
