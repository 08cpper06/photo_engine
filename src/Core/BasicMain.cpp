#include "Core/BasicMain.hpp"
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
	return true;
}

void TBasicMain::Update()
{
	;
}

void TBasicMain::Terminate()
{
	;
}