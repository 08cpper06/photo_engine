#include "Platform/OpenGL/Main.hpp"
#include "Platform/OpenGL/Window.hpp"
#include <list>
#include <GLFW/glfw3.h>
#include <iostream>


static void error_callback(int error, const char* desc) {
	std::cout << "E" << error << ": " << desc << std::endl;
}

std::shared_ptr<TBasicWindow> TOpenGLMain::CreateWindow(int Width, int Height)
{
	std::shared_ptr<TBasicWindow> Window = TOpenGLWindow::CreateWindow({ Width, Height });
	WindowList.push_back(Window);
	return Window;
}

bool TOpenGLMain::Init()
{
	glfwSetErrorCallback(error_callback);
	return glfwInit();
}
void TOpenGLMain::MainLoop()
{
	std::list<int> RemoveList;
	int Index;
	while (WindowList.size())
	{
		Index = 0;
		for (auto Itr = WindowList.begin(); Itr != WindowList.end(); ++Itr)
		{
			(*Itr)->Update();
			if ((*Itr)->GetStatus() == EWindowStatus::Closed)
			{
				RemoveList.push_back(Index);
			}
			++Index;
		}
		for (int Item : RemoveList)
		{
			WindowList.erase(WindowList.begin() + Item);
		}
		RemoveList.clear();
	}
}
void TOpenGLMain::Terminate()
{
	glfwTerminate();
}