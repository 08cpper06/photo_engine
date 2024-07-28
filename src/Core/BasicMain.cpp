#include "Core/BasicMain.hpp"
#include "Core/BasicRenderer.hpp"
#include "Core/ThreadManager.hpp"
#include "Platform/OpenGL/Main.hpp"



TBasicMain* TBasicMain::Get()
{
	return Instance.get();
}

bool TBasicMain::Init(EExecuteType Type)
{
	switch (Type) {
	case EExecuteType::OpenGL:
		Instance = std::make_unique<TOpenGLMain>();
		return Instance->Init();
	case EExecuteType::Native:
		return false;
	}
	return false;
}

bool TBasicMain::Init()
{
	ThreadManager::Get()->Init();
	ThreadManager::Get()->AddNewThread(EExecuteThreadType::RenderThread, [this](EExecuteThreadType) {
		while (!ThreadManager::Get()->IsRequestTerminate()) {
			this->Rendering();
			std::this_thread::yield();
		}
	});
	int Count = std::thread::hardware_concurrency();
	for (; Count; --Count)
	{
		ThreadManager::Get()->AddNewThread(EExecuteThreadType::WorkderThread, [](EExecuteThreadType Type) {
			ThreadManager::Get()->InternalExecute(Type);
		});
	}
	return true;
}

void TBasicMain::Rendering()
{
	for (std::shared_ptr<TBasicWindow>& Ptr : WindowList)
	{
		Ptr->GetRenderer()->Rendering();
	}
}

void TBasicMain::Update()
{
	;
}

void TBasicMain::Terminate()
{
	ThreadManager::Get()->Terminate();
}