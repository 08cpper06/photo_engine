#pragma once


class TBasicRenderer
{
public:
	virtual ~TBasicRenderer() = default;

	virtual void Rendering() = 0;
};