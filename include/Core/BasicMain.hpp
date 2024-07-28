#pragma once
#include "../Core/BasicWindow.hpp"
#include "../Singleton.hpp"
#include <vector>


enum class EExecuteType {
	OpenGL,
	Native,
};

class TBasicMain :
	public ISingleton
{
public:
	virtual ~TBasicMain() = default;

	static TBasicMain* Get();
	
	virtual std::shared_ptr<TBasicWindow> CreateWindow(int Width, int Height) = 0;

	static bool Init(EExecuteType Type);

	virtual bool Init() override;
	virtual void MainLoop() = 0;
	virtual void Terminate() override;
	void Update();

protected:
	inline static std::unique_ptr<TBasicMain> Instance = nullptr;
	std::vector<std::shared_ptr<TBasicWindow>> WindowList;
};