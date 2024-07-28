#pragma once
#include "../../Core/BasicRenderer.hpp"
#include "Window.hpp"


class TOpenGLWindow;

class TOpenGLRenderer :
	public TBasicRenderer
{
public:
	TOpenGLRenderer(TOpenGLWindow* Target);
	~TOpenGLRenderer();

	void Rendering() override;

private:
	TOpenGLWindow* TargetWindow;
};