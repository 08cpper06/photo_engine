#pragma once
#include "../Singleton.hpp"
#include <vector>
#include <mutex>
#include <thread>
#include <functional>


enum class EExecuteThreadType {
	WorkderThread,
	RenderThread,
};

struct TAsyncTask {
	TAsyncTask()
	{
		Task = [](){};
		Type = EExecuteThreadType::WorkderThread;
	}
	TAsyncTask(std::function<void(void)>&& InTask, EExecuteThreadType Type) :
		Task(std::move(InTask)),
		Type(Type)
	{}

	void operator()() const
	{
		Task();
	}

	std::function<void(void)> Task;
	EExecuteThreadType Type;
};

class ThreadManager :
	public ISingleton
{
public:
	~ThreadManager();

	static ThreadManager* Get();

	void AddNewThread(EExecuteThreadType InType, std::function<void(EExecuteThreadType)> InMain);

	bool IsRequestTerminate() const;

	bool Init() override;
	void Terminate() override;

	void TaskNew(TAsyncTask&& InTask);

public:
	void InternalExecute(EExecuteThreadType InType);

private:
	std::atomic<bool> IsRequestEnd;
	std::mutex TaskListLocker;
	std::list<TAsyncTask> TaskList;
	std::vector<std::thread> ThreadPool;
};