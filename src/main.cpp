#include "Core/BasicMain.hpp"


int main() {

	std::unique_ptr<TBasicMain> Main = TBasicMain::CreateMain(EExecuteType::OpenGL);
	if (!Main || !Main->Init())
	{
		return 1;
	}

	std::shared_ptr<TBasicWindow> Window = Main->CreateWindow(600, 400);
	if (!Window)
	{
		Main->Terminate();
	}

	Main->MainLoop();

	Main->Terminate();

	return 0;
}
