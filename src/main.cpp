#include "Core/BasicMain.hpp"


int main() {

	if (!TBasicMain::Init(EExecuteType::OpenGL))
	{
		return 1;
	}

	std::shared_ptr<TBasicWindow> Window = TBasicMain::Get()->CreateWindow(600, 400);
	if (!Window)
	{
		TBasicMain::Get()->Terminate();
	}
	std::shared_ptr<TBasicWindow> Window2 = TBasicMain::Get()->CreateWindow(600, 400);
	if (!Window2)
	{
		TBasicMain::Get()->Terminate();
	}

	TBasicMain::Get()->MainLoop();

	TBasicMain::Get()->Terminate();

	return 0;
}
