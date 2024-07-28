#pragma once
#include "../Singleton.hpp"
#include <vector>
#include <mutex>
#include <thread>
#include <functional>


struct TAsyncTask {
	TAsyncTask()
	{
		Task = [](){};
	}
	TAsyncTask(std::function<void(void)>&& InTask) :
		Task(std::move(InTask))
	{}

	void operator()() const
	{
		Task();
	}

	std::function<void(void)> Task;
};

class ThreadManager :
	public ISingleton
{
public:
	~ThreadManager();

	static ThreadManager* Get();

	bool Init(int InThreadCount);

	bool Init() override;
	void Terminate() override;

	void TaskNew(TAsyncTask&& InTask);

public:
	void InternalExecute();

private:
	std::atomic<bool> IsRequestEnd;
	std::mutex TaskListLocker;
	std::list<TAsyncTask> TaskList;
	std::vector<std::thread> ThreadPool;
};