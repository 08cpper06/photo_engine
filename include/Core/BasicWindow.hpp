#pragma once
#include <tuple>
#include <memory>


class TBasicRenderer;

enum class EWindowStatus {
	Unknown,
	Maximum,
	Minimum,
	Closed,
	Hidden,
	Virtual,
};

class TBasicWindow
{
public:
	virtual ~TBasicWindow() = default;

	virtual bool IsVirtual() const = 0;

	virtual std::pair<int, int> GetSize() const = 0;
	virtual void SetSize(int Width, int Height) const = 0;

	EWindowStatus GetStatus() const { return Status; }

	virtual void Update() = 0;

	virtual std::shared_ptr<TBasicRenderer> GetRenderer() const = 0;

	virtual void* GetNativeHandle() const = 0;

protected:
	EWindowStatus Status;
};