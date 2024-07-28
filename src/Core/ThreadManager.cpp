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

bool ThreadManager::Init(int InThreadCount)
{
	for (int Index = 0; Index < InThreadCount; ++Index)
	{
		Get()->ThreadPool.emplace_back([this]() {
			this->InternalExecute();
		});
	}
	return Get()->Init();
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

void ThreadManager::InternalExecute()
{
	while (!IsRequestEnd)
	{
		TAsyncTask Task;
		{
			std::lock_guard<std::mutex> locker(TaskListLocker);
			if (TaskList.size())
			{
				Task = std::move(TaskList.back());
				TaskList.pop_back();
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
