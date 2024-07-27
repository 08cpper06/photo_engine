#pragma once
#include "../Core/BasicWindow.hpp"
#include <vector>


enum class EExecuteType {
	OpenGL,
	Native,
};

class TBasicMain
{
public:
	virtual ~TBasicMain() = default;

	static std::unique_ptr<TBasicMain> CreateMain(EExecuteType Type);
	
	virtual std::shared_ptr<TBasicWindow> CreateWindow(int Width, int Height) = 0;

	virtual bool Init() = 0;
	virtual void MainLoop() = 0;
	virtual void Terminate() = 0;

protected:
	std::vector<std::shared_ptr<TBasicWindow>> WindowList;
};