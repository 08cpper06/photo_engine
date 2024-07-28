#include "Platform/OpenGL/Renderer.hpp"


TOpenGLRenderer::TOpenGLRenderer(TOpenGLWindow* Target) :
	TargetWindow(Target)
{}

TOpenGLRenderer::~TOpenGLRenderer()
{}

void TOpenGLRenderer::Rendering()
{
	glfwMakeContextCurrent(TargetWindow->Window);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glfwSwapBuffers(TargetWindow->Window);

	glfwMakeContextCurrent(nullptr);
}