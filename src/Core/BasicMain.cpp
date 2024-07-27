#include "Core/BasicMain.hpp"
#include "Platform/OpenGL/Main.hpp"



std::unique_ptr<TBasicMain> TBasicMain::CreateMain(EExecuteType Type)
{
	switch (Type) {
	case EExecuteType::OpenGL: return std::make_unique<TOpenGLMain>();
	case EExecuteType::Native: return nullptr;
	}
	return nullptr;
}