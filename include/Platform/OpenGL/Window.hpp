#include "../../Core/BasicWindow.hpp"
#include <GLFW/glfw3.h>


class TOpenGLWindow :
	public TBasicWindow
{
public:
	TOpenGLWindow(GLFWwindow* Window);
	~TOpenGLWindow() = default;

	static std::shared_ptr<TOpenGLWindow> CreateWindow(const std::pair<int, int>& Size);

	bool IsVirtual() const override;
	std::pair<int, int> GetSize() const override;
	void SetSize(int Width, int Height) const override;

	virtual void Update() override;

	std::shared_ptr<TBasicRenderer> GetRenderer() const override;

	void* GetNativeHandle() const;

private:
	GLFWwindow* Window;
};