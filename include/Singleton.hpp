#pragma once


class ISingleton {
public:
	virtual ~ISingleton() = default;

	virtual bool Init() = 0;
	virtual void Terminate() = 0;
};