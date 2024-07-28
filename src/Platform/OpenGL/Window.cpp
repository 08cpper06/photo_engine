#include "Platform/OpenGL/Window.hpp"
#include "Core/ThreadManager.hpp"


TOpenGLWindow::TOpenGLWindow(GLFWwindow* Window) :
	Window(Window)
{
	Renderer = std::make_shared<TOpenGLRenderer>(this);
}

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
	if (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
	}
	else
	{
		{
			std::lock_guard<std::mutex> locker(HandleLocker);
			glfwDestroyWindow(static_cast<GLFWwindow*>(Window));
			Window = nullptr;
			Renderer = nullptr;
		}
		Status = EWindowStatus::Closed;
	}
}

std::shared_ptr<TBasicRenderer> TOpenGLWindow::GetRenderer() const
{
	return Renderer;
}

void TOpenGLWindow::GetNativeHandle(std::function<void(void*)>&& InGetter)
{
	std::lock_guard<std::mutex> locker(HandleLocker);
	InGetter(Window);
}
