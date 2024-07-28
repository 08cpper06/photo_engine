#include "Core/BasicMain.hpp"
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
	ThreadManager::Get()->AddNewThread(EExecuteThreadType::RenderThread);
	int Count = std::thread::hardware_concurrency();
	for (; Count; --Count)
	{
		ThreadManager::Get()->AddNewThread(EExecuteThreadType::WorkderThread);
	}
	return true;
}

void TBasicMain::Update()
{
	;
}

void TBasicMain::Terminate()
{
	ThreadManager::Get()->Terminate();
}