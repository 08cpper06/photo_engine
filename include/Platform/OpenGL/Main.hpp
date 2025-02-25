#include "../../Core/BasicMain.hpp"


class TBasicWindow;

class TOpenGLMain :
	public TBasicMain
{
public:
	~TOpenGLMain() = default;
	
	std::shared_ptr<TBasicWindow> CreateWindow(int Width, int Height);

	bool Init() override;
	void MainLoop() override;
	void Terminate() override;

};