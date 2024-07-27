#include "Platform/OpenGL/Window.hpp"


TOpenGLWindow::TOpenGLWindow(GLFWwindow* Window) :
	Window(Window)
{}

std::shared_ptr<TOpenGLWindow> TOpenGLWindow::CreateWindow(const std::pair<int, int>& Size) {
	GLFWwindow* Window = glfwCreateWindow(Size.first, Size.second, "Preview", nullptr, nullptr);
	if (Window)
	{
		return std::make_shared<TOpenGLWindow>(Window);
	}
	return nullptr;
}

bool TOpenGLWindow::IsVirtual() const
{
	return false;
}
std::pair<int, int> TOpenGLWindow::GetSize() const
{
	int Width, Height;
	if (!Window)
	{
		return { -1, -1 };
	}
	glfwGetWindowSize(Window, &Width, &Height);
	return { Width, Height };
}

void TOpenGLWindow::SetSize(int Width, int Height) const
{
	glfwSetWindowSize(Window, Width, Height);
}

void TOpenGLWindow::Update()
{
	glfwMakeContextCurrent(Window);
	if (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
	}
	else
	{
		glfwDestroyWindow(Window);
		Status = EWindowStatus::Closed;
	}
}

std::shared_ptr<TBasicRenderer> TOpenGLWindow::GetRenderer() const
{
	return nullptr;
}

void* TOpenGLWindow::GetNativeHandle() const
{
	return reinterpret_cast<void*>(Window);
}
